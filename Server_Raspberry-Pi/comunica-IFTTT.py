# Consoante os dados, comunica com IFTTT
# @status: inc

host = "maker.ifttt.com";
apiKey = "dh0w-_fzIG-x02VrAHNnpa";     # key da recipe do Pedro

int valor = 0;

# se valor == 0, n faz nada
valor = 1

# se valor == 1, envia p. IFTTT
url_recipe = '/trigger/door_status/with/key/'
url_recipe += apiKey

print('Requesting URL: %s' + url_recipe)
# Enviar pedido para IFTTT
abc('POST ') + url + ' HTTP/1.1\r\n' +
        'Host: ' + host + '\r\n' + 
        'Content-Type: application/x-www-form-urlencoded\r\n' + 
        'Content-Length: 13\r\n\r\n' +
        'value1 = ' + door_state + '\r\n'


    #String url = "/trigger/door_status/with/key/";
    #url += apiKey;
    #//Serial.println(host);
          
    #Serial.print("Requesting URL: ");
    #Serial.println(url);
    #client.print(String("POST ") + url + " HTTP/1.1\r\n" +
          #"Host: " + host + "\r\n" + 
          #"Content-Type: application/x-www-form-urlencoded\r\n" + 
          #"Content-Length: 13\r\n\r\n" +
          #"value1=" + door_state + "\r\n");    

