# Provide a Flask-based MJPEG endpoint that streams live camera frames with a timestamp overlay to web clients.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-4b-camera-module-build-timelapse
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from flask import Flask, Response
from picamera2 import Picamera2
import cv2
from datetime import datetime

app = Flask(__name__)
camera = Picamera2()
camera.configure(camera.create_preview_configuration(main={"format": 'XRGB8888', "size": (1920, 1080)}))
camera.start()

def generate_frames():
    while True:
        frame = camera.capture_array()

        # Get the current time in hour:minute format
        current_time = datetime.now().strftime("%H:%M")

        # Define the position and font for the time overlay
        position = (frame.shape[1] - 200, 50)  # Adjust the position (x, y)
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 1
        color = (255, 255, 255)  # White color
        thickness = 2

        # Overlay the time on the frame
        cv2.putText(frame, current_time, position, font, font_scale, color, thickness, cv2.LINE_AA)

        # Encode the frame as a JPEG image
        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        # Yield the frame to the response stream
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
