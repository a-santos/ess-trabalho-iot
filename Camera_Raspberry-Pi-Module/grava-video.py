# Grava vídeo e grava num ficheiro
# @status: test

import picamera
from time import sleep

# Configs. da camera PI
camera = picamera.PiCamera()
camera.sharpness = 0
camera.contrast = 0
camera.brightness = 50
camera.saturation = 0
camera.ISO = 0
camera.video_stabilization = False
camera.exposure_compensation = 0
camera.exposure_mode = 'auto'
camera.meter_mode = 'average'
camera.awb_mode = 'auto'
camera.image_effect = 'none'
camera.color_effects = None
camera.rotation = 0
camera.hflip = False
camera.vflip = False
camera.crop = (0.0, 0.0, 1.0, 1.0)
camera.hflip = True
camera.vflip = True

# Local onde será guardado o vídeo
video_dir = '/home/pi/ess_trabalho/video/'

# Grava vídeo durante 5 segs.
print('A capturar video (5 segundos)...')
camera.start_recording(video_dir + 'video2.h264')
sleep(5)

camera.stop_recording()
print('Vídeo guardado em --> %s' % video_dir)

camera.close()