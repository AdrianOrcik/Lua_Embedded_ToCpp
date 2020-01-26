
--player = GameObject.Create()
--
--player:Move(5,7)
--player:Draw()
--
--player:Move(5,10)
--player:Draw()

-- sprite = Sprite.Create()
-- sprite:LoadSprite("src/Sprites/Tank_1.txt",3)
-- sprite:Draw(10,15)



--Test
--
-- Tank1 = Sprite.Create()
-- Tank1:LoadSprite("src/Sprites/Tank_1.txt",3)
-- Tank1:Draw(10,15)
--
--Tank2 = Sprite.Create()
--Tank2:LoadSprite("src/Sprites/Tank2.txt",3)
--Tank2:Draw(50,15)
--

--angle = Math.DegToRad(45)
--print(angle)
--
--Console.Sleep(2)
--Console.Clear()

-- player = GameObject.Create()
-- player:Move(5,7)
-- player:Draw()
-- print(player.x)
-- player.x = 10
-- print(player.x)

--canvas = Canvas.Create()
--mainText = "Value: " .. tostring(5)
--print(mainText)
--canvas:Text(10,15,"Value: " .. tostring(10))
--input = canvas:InputField_Float(10,16,"Test input:")
--print(string.format("input: %.1f",input))
--print(input)

--Animations
PlayerAnimation = Animator.Create()
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_1.txt",3)
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_2.txt",3)
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_3.txt",3)

TankAnimation = Animator.Create()
TankAnimation:AddToSheet("src/Sprites/Explosion_1.txt",4)
TankAnimation:AddToSheet("src/Sprites/Explosion_2.txt",4)
TankAnimation:AddToSheet("src/Sprites/Explosion_3.txt",4)

--Functions
UICanvas    = Canvas.Create()

Player      = Sprite.Create()
Player:LoadSprite("src/Sprites/Tank_1.txt",3)
IsPlayerShoot = false

EnemyObj    = GameObject.Create()
EnemySprite       = Sprite.Create()
EnemySprite:LoadSprite("src/Sprites/Tank_2.txt",3)
EnemyHealth = 2
EnemyAlive = true

function IsEnemyInDistance(_distance, _enemyPos)
        local min = _distance - 5
        local max = _distance + 5
        if((_enemyPos >= min) and (_enemyPos <= max))
            then return true end
    do return false end
end

function EnemySetPosition(_x,_y)
    EnemyObj.x = _x
    EnemyObj.y = _y
end

function Enemy()
    EnemySetPosition(80,10)
    if EnemyHealth > 0 then 
        UICanvas:Text(EnemyObj.x + 2,EnemyObj.y - 1,"HP: " .. tostring(EnemyHealth))
        EnemySprite:Draw(EnemyObj.x,EnemyObj.y)
    else
        if EnemyAlive == true and IsPlayerShoot == false then
            TankAnimation:Animate(EnemyObj.x,EnemyObj.y,100)
            EnemyAlive = false
            Game()
        end
    end
end

function Game()
    UICanvas:Text(0,0,"Tank Shot 2D - Embedded Lua to CPP")
    
    Enemy()
    
    UICanvas:Text(81,12,".")
    
    Player:Draw(5,10)

    if IsPlayerShoot == true then
        PlayerAnimation:Animate(5,10,100)
        IsPlayerShoot = false
        Game()
    end

end

function PlayerInput()
    local playerAngle = UICanvas:InputField_Int(0,20,"Angle: ")
    local playerSpeed = UICanvas:InputField_Int(0,21,"Speed: ")
    local distance = Math.MaxDistance(playerSpeed,playerAngle)
    print(distance)

    local result = IsEnemyInDistance(distance,EnemyObj.x)
    if result == true then
        EnemyHealth = EnemyHealth - 1
        IsPlayerShoot = true
    end

    print(result)
end

--Main core loop
while true do
    Game() --Draw idle scene 
    if IsPlayerShoot == false then
        PlayerInput()
    end
    Game() --Draw scene with animations
    Console.Sleep(1)
    Console.Clear()
end
