# Captures continuous JPEG frames from the Raspberry Pi camera and serves them as an MJPEG stream via a Flask /video_feed endpoint.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-camera-stream-video-flask
# Parts used: https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import io
import picamera
from flask import Flask, Response

### You can donate at https://www.buymeacoffee.com/mmshilleh if I saved you time
### Subscribe https://www.youtube.com/@mmshilleh/videos

app = Flask(__name__)

def generate_frames():
    with picamera.PiCamera() as camera:
        camera.resolution = (640, 480)
        camera.framerate = 24
        stream = io.BytesIO()

        for _ in camera.capture_continuous(stream, 'jpeg', use_video_port=True):
            stream.seek(0)
            yield b'--frame\r\nContent-Type: image/jpeg\r\n\r\n' + stream.read() + b'\r\n'
            stream.seek(0)
            stream.truncate()

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, threaded=True)
