# main.py
import sys
import os
import threading
import cv2
import numpy as np
from moviepy import VideoFileClip, VideoClip
from PyQt5.QtCore import Qt, QThread, pyqtSignal, QTimer
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QFileDialog, QProgressBar,
    QMessageBox, QCheckBox
)

# ----------------------------------------------------------------------
# Style‑transfer helper (demo using cv2.stylization)
# ----------------------------------------------------------------------
def stylize_frame(frame, stylization_level=0.5):
    """
    Apply a quick stylization filter to an OpenCV frame.
    For production, replace with your neural style‑transfer model.
    """
    dst = cv2.stylization(frame, sigma_s=60, sigma_r=stylization_level)
    return dst


# ----------------------------------------------------------------------
# Video processing thread
# ----------------------------------------------------------------------
class VideoProcessor(QThread):
    progress_changed = pyqtSignal(int)
    finished = pyqtSignal(str)
    error = pyqtSignal(str)

    def __init__(self, src_path, style_path, out_path, parent=None):
        super().__init__(parent)
        self.src_path = src_path
        self.style_path = style_path
        self.out_path = out_path

    def run(self):
        try:
            # Load the style video to extract one representative frame
            style_clip = VideoFileClip(self.style_path)
            style_frame = style_clip.get_frame(0)
            style_frame = cv2.cvtColor(style_frame, cv2.COLOR_RGB2BGR)

            # Load source video
            src_clip = VideoFileClip(self.src_path)
            fps = src_clip.fps
            duration = src_clip.duration
            total_frames = int(fps * duration)

            out_frames = []

            # Process each frame
            for i, frame in enumerate(src_clip.iter_frames()):
                # Convert RGB->BGR for OpenCV
                frame_bgr = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

                # Simple demonstration: blend source with style frame
                # In real use, replace this with a neural network call.
                stylized = stylize_frame(frame_bgr, stylization_level=0.5)

                # Convert back to RGB for MoviePy
                stylized_rgb = cv2.cvtColor(stylized, cv2.COLOR_BGR2RGB)

                out_frames.append(stylized_rgb)

                # Emit progress
                percent = int((i + 1) / total_frames * 100)
                self.progress_changed.emit(percent)

            # Write output
            out_clip = VideoClip(lambda t: out_frames[int(t * fps)], duration=duration)
            out_clip.write_videofile(self.out_path, fps=fps, codec='libx264', audio_codec='aac')
            self.finished.emit(self.out_path)

        except Exception as e:
            self.error.emit(str(e))


# ----------------------------------------------------------------------
# Main GUI
# ----------------------------------------------------------------------
class StyleVideoEditor(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Style‑Transfer Video Editor")
        self.resize(600, 300)

        self.src_path = None
        self.style_path = None
        self.out_path = None

        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()

        # 1️⃣ Source video
        src_layout = QHBoxLayout()
        self.src_label = QLabel("Source video: (none)")
        btn_src = QPushButton("Browse…")
        btn_src.clicked.connect(self.choose_src)
        src_layout.addWidget(self.src_label)
        src_layout.addWidget(btn_src)
        layout.addLayout(src_layout)

        # 2️⃣ Style video
        style_layout = QHBoxLayout()
        self.style_label = QLabel("Style video: (none)")
        btn_style = QPushButton("Browse…")
        btn_style.clicked.connect(self.choose_style)
        style_layout.addWidget(self.style_label)
        style_layout.addWidget(btn_style)
        layout.addLayout(style_layout)

        # 3️⃣ Output location
        out_layout = QHBoxLayout()
        self.out_label = QLabel("Output: (auto‑generated)")
        btn_out = QPushButton("Browse…")
        btn_out.clicked.connect(self.choose_out)
        out_layout.addWidget(self.out_label)
        out_layout.addWidget(btn_out)
        layout.addLayout(out_layout)

        # 4️⃣ Progress bar
        self.progress_bar = QProgressBar()
        self.progress_bar.setRange(0, 100)
        layout.addWidget(self.progress_bar)

        # 5️⃣ Run button
        self.run_btn = QPushButton("Run Style‑Transfer")
        self.run_btn.clicked.connect(self.start_processing)
        layout.addWidget(self.run_btn)

        self.setLayout(layout)

    def choose_src(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Select source video", "", "Video Files (*.mp4 *.mov *.avi *.mkv)"
        )
        if file_path:
            self.src_path = file_path
            self.src_label.setText(os.path.basename(file_path))

    def choose_style(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Select style video", "", "Video Files (*.mp4 *.mov *.avi *.mkv)"
        )
        if file_path:
            self.style_path = file_path
            self.style_label.setText(os.path.basename(file_path))

    def choose_out(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Save output video", "", "MP4 (*.mp4);;AVI (*.avi)"
        )
        if file_path:
            self.out_path = file_path
            self.out_label.setText(os.path.basename(file_path))

    def start_processing(self):
        if not self.src_path or not self.style_path:
            QMessageBox.warning(self, "Missing files", "Please select both source and style videos.")
            return

        # Default output path if not chosen
        if not self.out_path:
            base, ext = os.path.splitext(self.src_path)
            self.out_path = f"{base}_stylized{ext}"
            self.out_label.setText(os.path.basename(self.out_path))

        self.run_btn.setEnabled(False)
        self.progress_bar.setValue(0)

        self.thread = VideoProcessor(self.src_path, self.style_path, self.out_path)
        self.thread.progress_changed.connect(self.progress_bar.setValue)
        self.thread.finished.connect(self.on_finished)
        self.thread.error.connect(self.on_error)
        self.thread.start()

    def on_finished(self, out_path):
        self.run_btn.setEnabled(True)
        QMessageBox.information(self, "Done", f"Stylized video saved to:\n{out_path}")

    def on_error(self, msg):
        self.run_btn.setEnabled(True)
        QMessageBox.critical(self, "Error", msg)


# ----------------------------------------------------------------------
# Run app
# ----------------------------------------------------------------------
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = StyleVideoEditor()
    win.show()
    sys.exit(app.exec_())