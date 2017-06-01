# Consoante os dados, comunica com IFTTT
# @status: test
#       criar recipe IFTTT q envia notific. p telm
#       fz 2 envios diferentes (água, comida)
#       optimizar: só enviar qd != do val. anterior

import requests

host = "maker.ifttt.com";
apiKey = "";                    # key da recipe do Afonso

int valor = 0;

url_recipe = '/trigger/door_status/with/key/'
url_recipe += apiKey

# se valor == 0, n faz nada

valor = 1
# se valor == 1, envia p. IFTTT
sendIfttt(valor)

def sendIfttt(valor):
    print('A enviar para IFTTT... Requesting URL: %s' + url_recipe)

    report = {}
    report["value1"] = valor
    requests.post("https://maker.ifttt.com/trigger/**NAME-OF-CHANNEL/with/key/**ID-KEY", 
        data = report)   