-- Comments in Lua look like this

math.randomseed(os.time())

-- the initial background colour
colour = 100
-- the game starts at this level
level = 25
-- the player starts the game with this many lives
lives = 10
-- the speed that the mothership will travel when spawned
mothershipSpeed = 2.0

-- sprites for the player to use
playerSprite = "assets/Ufoph.bmp"
playerSprTurn = "assets/UfophRight.bmp"



-- A simple Vector2 object
startpos = { x = 625, y = 625}

-- bool
credits = false

-- float
floatyPoint = 26.8

-- double
doublePoint = 53.6

-- handles random events like mothership spawns and ufo shooting
function rng()
	return math.random(1, 10000)
end

-- move the player right
function right(x, directionFlag)
	x = x + 5
	directionFlag = 1

	if (x >= 910)
	then
		x = 910
	end
	
	return x, directionFlag
end

-- move the ufos left and right, they get faster as more are killed
function moveUfo(x, currentFrame, ufoKilled, level, dirFlag)
	currentFrame = currentFrame + 0.1

	moveSpeed = 0.5 + (ufoKilled / 20) + (level / 80)

	if (dirFlag == true)
	then
		x = x + moveSpeed
	else
		x = x - moveSpeed
	end

	if (currentFrame >= 1.9)
	then
		currentFrame = 0
	end

	return x, currentFrame
end


-- message for next level
function callNextLvlMessage()
	display_message("Next wave...", 1)
end

-- message when you beat the game
function callWinMessage()
	display_message("Victory!!!", 1)
end

-- message displayed when the game starts
function callStartMessage()
	game_start_message("WE'RE UNDER ATTACK!", 5, "Invaders in %d...", 3)
end

-- increment the player score
function setPlayerScore(score)
	CDispatcher("setScore", score)
end

-- player dies - instant game over
function killPlayer()
	CDispatcher("kill")
end