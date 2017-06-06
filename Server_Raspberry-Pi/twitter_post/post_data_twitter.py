#!/usr/bin/env python
# -*- coding: utf-8 -*-

# v0 Postar diretamente leitura
# v1 Postar 1 tweet com a última leitura do nível da água+hora, lida de 1 txt
# *v2 Só postar qd nível chega a valor crítico?

import sys
import os
from twython import Twython

CONSUMER_KEY = '7RwThUZOLfysVHvRWk2OzPnY1'
CONSUMER_SECRET = 'xI4PFayQj1QD0BW7qjAhDFJ3NX27muJQEYSFVMYI2I55321kFH'
ACCESS_KEY = '750721019875319809-Qo7lfX1Vt34SwuJ4DalWyXxRLOLBdoA'
ACCESS_SECRET = 'cGz8tiBWKM5d3DxSoInMWI8Us6GhQM21IbcdHztpV4Eou'

#__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))

api = Twython(CONSUMER_KEY,CONSUMER_SECRET,ACCESS_KEY,ACCESS_SECRET) 
#
def postTweet():
    try:
        print ('ola')        # Debug
	api.update_status(status = 'ola')
        return None
    except IOError:
        return None

postTweet()