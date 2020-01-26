--Projectile particles
ProjectileArr = {}
ProjectileIndex = 1;

--Animations
PlayerAnimation = Animator.Create()
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_1.txt",3)
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_2.txt",3)
PlayerAnimation:AddToSheet("src/Sprites/Tank_Shot_3.txt",3)

TankAnimation = Animator.Create()
TankAnimation:AddToSheet("src/Sprites/Explosion_1.txt",4)
TankAnimation:AddToSheet("src/Sprites/Explosion_2.txt",4)
TankAnimation:AddToSheet("src/Sprites/Explosion_3.txt",4)

--UI Canvas
UICanvas    = Canvas.Create()

--Player properties
Player      = Sprite.Create()
Player:LoadSprite("src/Sprites/Tank_1.txt",3)
IsPlayerShoot = false

--Enemy properties
EnemyObj    = GameObject.Create()
EnemySprite       = Sprite.Create()
EnemySprite:LoadSprite("src/Sprites/Tank_2.txt",3)
EnemyHealth = 2
EnemyAlive = true

--Functions
function IsEnemyInDistance(_distance, _enemyPos)
    --Calcualtion if player hit enemy tank
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

    --Enemy behavior of tank render & tank animation
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
    
    --Projectile particles draw 
    for i = 1 , ProjectileIndex do
        if(ProjectileArr[i] ~= nill) then
            UICanvas:Text(ProjectileArr[i],12,".")
        end
    end

    Player:Draw(5,10)

    --If player is currently in shoot state play animation
    if IsPlayerShoot == true then
        PlayerAnimation:Animate(5,10,100)
        IsPlayerShoot = false
        Game()
    end
end

function PlayerInput()
    --Player projectile input
    local playerAngle = UICanvas:InputField_Int(0,20,"Angle: ")
    local playerSpeed = UICanvas:InputField_Int(0,21,"Speed: ")
    local distance = Math.MaxDistance(playerSpeed,playerAngle)
    print(distance)

    --Check if player hit enemy
    local result = IsEnemyInDistance(distance,EnemyObj.x)
    if result == true then
        EnemyHealth = EnemyHealth - 1
    end

    --Settings for animation & projectile particles
    IsPlayerShoot = true
    ProjectileArr[ProjectileIndex] = distance
    ProjectileIndex = ProjectileIndex + 1

    print(result)
end

--Main core loop
while true do
    --Draw idle scene 
    Game() 
    if IsPlayerShoot == false then
        PlayerInput()
    end
    --Draw scene with animations
    Game() 
    Console.Sleep(1)
    Console.Clear()
end
