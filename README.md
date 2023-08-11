# printRBTree2d
This is a simple program that builds a random Red-Black tree and then prints a vertical 2d text based tree.

# Sample Output
```
                                                             39                                                        
                                              /                               \                                  
                              20                                                              81                
                      /               \                                               /               \            
              16                              27                              61                              90           
          /       \                       /       \                       /       \                       /       \   
      6               17              24              32              47              68              85              95     
    /   \                           /               /               /   \           /   \           /   \           /   \      
  4       13                      22              29              45      58      65      72      84      87      93      98    
                                                                 /       /               /                       / \       \     
                                                                41      48              71                      91  94      99
```
# Note
The program will adapt to the size of the tree, but if there is a tree with a depth greater than 6, the lines will wrap and mess up the formatting. You would need to view the output with smaller text size or a higer resolution monitor.
Values greater than 999 will also mess with the formatting.
