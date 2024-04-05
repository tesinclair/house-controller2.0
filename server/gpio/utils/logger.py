

class Logger():
    @staticmethod
    def log(exType, exVal, traceback):
        print(f"""
              [GPIO ERROR LOG]
              [TYPE]: {exType}
              [VALUE]: {exVal}
              [TRACEBACK]: {traceback}
              """)

              
              
