import queue
from gpio import LedStrip
from sockets import GPIOSocket
from threading import Thread

def handle_socket(queue):
    with GPIOSocket(queue) as s:
        try:
            while True:
                s.run()
        except KeyboardInterrupt:
            print("Exiting")

def main():
    q = queue.Queue()

    try:
        thread = Thread(target=handle_socket, args=[q])

        thread.start()

        with LedStrip(q) as controller:
            while True:
                if not controller.next(None):
                    break

    except Exception as e:
        print("Exiting: {e}")

if __name__ == "__main__":
    main()
