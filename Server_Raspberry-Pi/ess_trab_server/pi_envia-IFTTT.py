#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Consoante os dados, comunica com IFTTT

import requests

url_recipe_water = 'https://maker.ifttt.com/trigger/pouca_agua//with/key/kdNe6V0RbYlqgbWc8q5sCXp9aFcW-hpAyhTclW_VD21';
url_recipe_food = 'https://maker.ifttt.com/trigger/pouca_comida/with/key/mpVubn3K94tvrEG1vKYnk8E0OuvGWSt3u2czfTs_aH9';
#apiKey = 'dh0w-_fzIG-x02VrAHNnpa';       # key da recipe do Pedro
valueWater = 0
valueFood = 0

#url_host_recipe += apiKey

def sendWaterIfttt(valueWater):
    print('Pouca ÁGUA! A enviar request para IFTTT: ' + url_recipe_water)

    report = {}
    report["value1"] = valueWater
    requests.post(url_recipe_water, data = report)

def sendFoodIfttt(valueFood):
    print('Pouca COMIDA! A enviar request para IFTTT: ' + url_recipe_food)

    report = {}
    report["value1"] = valueFood
    requests.post(url_recipe_food, data = report)

# se valueWater == 1, envia p. IFTTT
valueWater = 1
sendWaterIfttt(valueWater)   

# se valueFood == 1, envia p. IFTTT
valueFood = 1
sendFoodIfttt(valueFood)        