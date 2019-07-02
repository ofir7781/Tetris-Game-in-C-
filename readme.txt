Tetris Game notes:

Reviewer guidelines:

1. The shape bomb explodes when it touch the sides of the board and doesnt keep moving down,
    Otherwise you can't avoid getting your score decreased.

2. The score will always be a positive number. we build it in a way that the lowest score that the player can get is zero. 

3. When our shape is a bomb, and there is another shape on the left/right side of that bomb, 
    it will explode on that shape and all the blocks around it (3x3 blocks) only if we 
    will move the bomb to hit that shape with the keyboard(press right/left).
    Otherwise, it will keep moving to the buttom of the board and explodes on the first shape it will hit 
    and all the blocks around it (3x3 blocks).
    If it got to the bottom line it will explode there with all the blocks around it (3x3 blocks).

4. About line rotate - we imitate the rotate of the online tetris game, where the axis for the rotate alternately betweem the two center blocks.
    We also decided not to allow the user to rotate if he is too close to the edge.

5. the user cannot lose the game if the next shape is a bomb(intentionally because bomb explodes everything).

6. even if the joker is not standing on another block, it will still go down when rows are completed. 

7. we choose to make a different class for each type of shape in order to demonstrate the inheritance feature.
