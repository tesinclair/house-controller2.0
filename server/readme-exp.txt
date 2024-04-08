I have two servers here, one in python with fastapi. This will be depricated later down the line.

The reason I have a python server is for easy of development. It is easier to interface with the gpio module, and since speed and 
scallability aren't super high priorities I decided to make the server with python first, so I can get it done and create the app and site faster

Once I have developed everything, I intend to refactor the python server to a go server with gRPC to interface with the gpio. 
