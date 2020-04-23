'''
scenes = ['a','b','a','b','c','b','a','c','a','d','e','f','e','g','d','e','h','i','j','h','k','l','i','j']
          |                                  |                           |                               |

scenes = ['x','a','b','a','b','c','b','a','c','a','d','e','f','e','g','d','e','h','i','j','h','k','l','i','j']
         |   |                                   |                           |                               |

         maximize the number of subsequences without cutting any scenes in half
output: [1, 9, 7, 8]     

    x: 0, -
    a: 1, 9
    b: 2, 6
    c: 5, 8
    d: 10, 15
    e: 11, 16
    f: 12, -
    h: 17, 20
    i: 18, 23
    j: 19, 24
    k: 21, -
    l: 22, -
    
    *Don't need start index
'''

def cutScenes( scenes ):
    
    # Walk through scenes to store last index of each scene
    myDict = {}
    for i,scene in enumerate(scenes):
        myDict[scene] = i

    # Walk through scenes and cut subsequences
    start, end = 0, 0 # 0,0
    res = []
    for i,scene in enumerate(scenes):
        if i > end or i == len(scenes): # last element edge case
            res.append( end - start + 1 )
            start = i # reset new start
        if myDict[scene] > end:
            end = myDict[scene]

    return res



