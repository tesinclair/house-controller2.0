import queue
from .gpio import LedStrip
from .sockets import GPIOSocket
from threading import Thread

def handle_socket(queue):
    with GPIOSocket(queue) as s:
        s.run()

def main():
    queue = queue.Queue()

    try:
        thread = Thread(target=handle_socket, args=[queue])
        thread.start()

        while True:
            with LedStrip(queue) as controller:
                if not controller.next(None):
                    break

    except Exception as e:
        print("Exiting: {e}")

if __name__ == "__main__":
    main()
