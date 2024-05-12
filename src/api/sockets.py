import json
import socket
import queue
import sys

sys.path.append("./utils")
import utils

class GPIOSocket:
    def __init__(self, queue):
        self.queue = queue

    def __enter__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(("0.0.0.0", 6767))
        self.sock.listen(1) # Should not recieve concurrect requests

        print("[SERVER]: Listening on Lan: 6767")

        return self

    def __exit__(self, *args):
        self.sock.shutdown(1)
        self.sock.close()
        print("[SERVER]: Closed socket")

    def run(self):
        while True:
            self.conn, self.addr = self.sock.accept()

            if not self.validate_ip():
                print(f"[SERVER]: Refusing connection from {self.addr}")
                self.remove_client()
                break

            print(f"[SERVER]: Accepting connection from {self.addr}")

            encoded_data = self.conn.recv(1024)
            if not encoded_data:
                break

            self.data = encoded_data.decode("UTF-8")

            if not self.validate_data():
                print(f"[SERVER]: Recieved bad request: {self.data} from {self.addr}")
                conn.sendall(bytes("BAD REQUEST", 'UTF-8'))
                self.remove_client()
                break
            
            print(f"[SERVER]: Recieved ok request: {self.data} from {self.addr}")
            self.queue.put(data)
            self.conn.sendall(bytes("OK", "UTF-8"))
            print(f"[SERVER]: Request accepted. Removing {self.addr}")
            self.remove_client()

    def validate_ip(self):
        with open("hidden/whitelist.txt", "r") as f:
            if self.addr not in f.read():
                return False
            
        return True

    def validate_data(self):
        grammar = None

        if ":" not in self.data:
            return False

        with open("util/grammar.json", "r") as json_raw:
            grammar = json.load(json_raw)

        key, val = self.data.split(":")
        allowed_data = grammar.get(key)

        if allowed_data == None:
            return False
        
        if val not in allowed_data:
            return False

        return True

    def remove_client(self):
        self.conn.close()
        print(f"[SERVER]: Closed connection with {self.conn}")
        self.conn = None
        self.addr = None
