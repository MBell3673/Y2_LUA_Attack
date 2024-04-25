-- Comments in Lua look like this

math.randomseed(os.time())

-- the initial background colour
colour = 100
-- the game starts at this level
level = 25
-- the player starts the game with this many lives
lives = 10
-- the speed that the mothership will travel when spawned
mothershipSpeed = 2.5

-- sprites for the player to use
playerSprite = "assets/Ufoph.bmp"
playerSprTurn = "assets/UfophRight.bmp"



-- A simple table with 2 elements, can be translated into a Vector2 struct that we made in C
startpos = { x = 625, y = 625}

-- test for Lua bool, toggles showing credits at the bottom of the screen
credits = true

-- both of these numbers were just to test that I can get both float and double from Lua
floatyPoint = 26.8
doublePoint = 53.6

-- generates a random number - handles random events like mothership spawns and ufo shooting
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

-- player dies - instant game over (called when ufos reach the bottom)
function killPlayer()
	CDispatcher("kill")
end