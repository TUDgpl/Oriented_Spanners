import random
import tools

class Generator:
    def __init__(self,args):
        self.seed = args.seed[0]
        random.seed(self.seed)
        self.width = args.width[0]
        self.height = args.height[0]
        self.model = args.model[0]
        self.point_size = args.point_size
        self.output_file = args.output[0]
        self.Points = set()
    def info(self):
        print(f'Width:{self.width}')
        print(f'Height:{self.height}')
        print(f'Model:{self.model}')
        print(f'numbe of points:{self.point_number}')
        print(*self.Points,sep="")



