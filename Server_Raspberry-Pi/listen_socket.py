import socket

HOST = ''              # Endereco IP do Servidor
PORT = 80              # Porta que o Servidor tem à escuta

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
BUFFER_SIZE = 20
origem = (HOST, PORT)

tcp.bind(origem)
tcp.listen(1)

while True:
    con, cliente = tcp.accept()
    print 'Conectado por', cliente
    while True:
        msg = con.recv(1024)
        if not msg: break
        print cliente, msg
    print 'Finalizando conexão do cliente', cliente
    con.close()