

while(True):
    print("Enter correct filename:")
    input_filename = input() #'readme.txt'
    #directory '_out' should exist with the files
    output_filename = open("_out/"+input_filename, "w")
    try:
        with open(input_filename) as f:
            lines = f.readlines()
            for line in lines:
                print(line, end = '')
                w = float(line)
                output_filename.write(str(round(w,6))+'\n')

            print('\n')
            f.close()
            output_filename.close()
            
    except Exception as e:
        print(e)
