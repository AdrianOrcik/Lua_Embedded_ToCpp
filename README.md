:pencil: 2D Console Tank Game
---------
LUA based project build on CPP Embedded API

:bulb: Idea
---------
Create game-oriented LUA to C++ based embedded project with the easy game loop.
The game loop will be used public API in LUA from the native C++ app.

#### Game Loop
Point of the small game is shot enemy tank by set angle and speed of your projectile.
Projectiles is calculated by oblique litter formulas.

![image](https://user-images.githubusercontent.com/14979589/73132744-9a9b6980-4027-11ea-906c-40a675e8705d.png)

:tada: Result
---------
![TankShot](https://user-images.githubusercontent.com/14979589/73132692-fc0f0880-4026-11ea-813f-f802a2b4a8cc.gif)

:pushpin: Project Architecture
---------
### UML
![image](https://user-images.githubusercontent.com/14979589/73133123-24016a80-402d-11ea-9d7d-bbf3e5c00e40.png)

### File Structure
* src/
  * Components/
  * LuaScripts/
  * Sprites/
* DebugLuaStack.h
* lua.hpp

:card_file_box: LUA API
---------
#### Canvas
* void Create()
  * Create canvas object
* void Text(x,y,message)
  * Print message on x,y position in console
* int InputField_Int(x,y,message)
  * Print message on x,y position in console and return input
* float InputField_Float(x,y,message)
  * Print message on x,y position in console and return input
 
```python
maincanvas = Canvas.Create()
value = maincanvas:InputField_Int(10,10,"Set Value")
maincanvas:Text(11,10,"Your Value: " + tostring(value))
```

#### GameObject
* void Create()
  * Create object
* void Set(x,y)
  * Set object position
* void Print()
  * Print object position on screen
  
```python
box = GameObject.Create()
box:Set(10,10)
```
  
#### Sprite
Sprite component is able to read ASII images from txt files
ImgSize - heigth of ASCII image in file
* void Create()
  * Create sprite object
* void LoadSprite(filePath,imgSize)
  * Load sprite img into object
* void Draw(x,y)
  * Draw sprite on x,y position in console

```python
playerImg = Sprite.Create()
playerImg:LoadSprite("sprites/player.txt",3)
playerImg:Draw(10,10)
```

#### Animator
Animator component is able to create frame by frame animations from ASCII images
* void Create()
  * Create animator controller object
* void AddToSheet(filePath,imgSize)
  * Load sprite from file and add to animation stack
* void Animate(x,y,frameDelay)
  * Draw frames as animated on x,y position in the console
  * frameDelay in miliseconds
  
```python
playerAnimator = Animator.Create()
playerAnimator:AddToSheet("sprites/explosion_1.txt",3)
playerAnimator:AddToSheet("sprites/explosion_2.txt",3)
playerAnimator:AddToSheet("sprites/explosion_3.txt",3)
playerAnimator:Animate(10,10,100)
```
  
#### Math (static)
* float DegToRad(radian)
  * Calculate degress to radians
* float MaxHeight(speed,angle)
  * Calculate max height what projectile is able to reach
* float MaxDistacnce(speed,angle)
  * Calculate max distance of object what projectile will triggered

```python
rad = Math.DegToRad(45)
print(rad)
```

#### Console (static)
* void Sleep(seconds)
  * Sleep code execution for defined time
* void Clear()
  * Clear console
  
```python
Console.Sleep(2)
Console.Clear()
```
