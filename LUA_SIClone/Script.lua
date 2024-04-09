-- Comments in Lua look like this

math.randomseed(os.time())

colour = 100
level = 25
lives = 10
playerSprite = "assets/ufoph.bmp"

-- A simple Vector2 object
startpos = { x = 625, y = 625}

-- bool
credits = false

-- float
floatyPoint = 26.8

-- double
doublePoint = 53.6


function rng()
	return math.random(1, 10000)
end


function right(x, currentFrame)
	x = x + 5

	if (x >= 910)
	then
		x = 910
	end

	if (currentFrame > 1.9)
	then
		currentFrame = 0
	end
	
	return x, currentFrame
end



function callNextLvlMessage()
	display_message("Next wave...", 1)
end

function callWinMessage()
	display_message("Victory!!!", 1)
end


function callStartMessage()
	game_start_message("WE'RE UNDER ATTACK!", 5, "Invaders in %d...", 3)
end

function setPlayerScore()
	CDispatcher("setScore", 5000)
end