# Maze-Cocos2Dx
Maze is a 2-player cross-platform game designed using Cocos2D-x, where Player1 &amp; Player2 have been seperated in a labrynith. Player1 has been poisoned and needs to get a magic healing potion from Player2 within 10s to survive. The labrynith is a 13x13 maze with only one possible route between the players. If the two characters can meet on time, the game generates another maze with the same size and time-limit. In case of failure, the game ends. Player2 can be controlled with A,W,S &amp; D keys and Player1 can be controlled with Arrow Keys.

As Cocos2d-x is a cross-platform game, it separates the cross-platform code from the platform dependent code during storage. All the cross-platform code is stored in a directory Classes. Platform dependent codes are stored in individual folders dedicated to a particular platform. Resources folder contains the common resources such as sprites, spritesheets, audio files etc.,

To allow more efficient memory allocation to sprites, COCOS2D provides for batch drawing through use of a sprite sheet cache, SpriteFrameCache from which sprites can be fetched. Further, all sprites/nodes have a pre-defined base coordinate, Anchor point. It can be used to dynamically simulate game effects for that sprites, specifically transformations. The Spritesheet used in this game was created using TexturePackerGUI. It contains the background image for our game, the Road & Block tiles and 4 images displaying the two characters in our game in different poses.

A soundtrack “Storybook.mp3” licensed under Creative Commons has been supported as background music through the use of SimpleAudioEngine API.

