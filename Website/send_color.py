

color = ""
def pass_color(color_in):
    color = color_in;
    ## determine whether color is hex or string // default type is color
    if color[:1] == '#' :
        color = '0x' + color[1:]
        red = int(color[3:4], 16)
        grn = int(color[5:6], 16)
        blu = int(color[7:8], 16)
        print '{0:d}, {1:d}, {2:d}'.format(red, grn, blu)
        return [red, grn, blu]



def send_to_AVR(colors):
    pass	
