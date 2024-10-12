
const canvas = document.getElementById('canvas')
const ctx = canvas.getContext('2d')
const CANVAS_WIDTH = canvas.width = 1200
const CANVAS_HEIGHT = canvas.height = 700

const play = document.getElementById('play')
const story = document.getElementById('story')
const menu = document.getElementById('menu')
const newGame = document.getElementById('newGame')
const newGameNew = document.getElementById('newGameNewMap')
const end = document.getElementById('end')
const lastPoint = document.getElementById('lastPoint')
const questBox = document.getElementById('questBox')
const quest = document.getElementById('quest')
const questButton1 = document.getElementById('questb1')
const questButton2 = document.getElementById('questb2')
const questTimer = document.getElementById('timer')
const response = document.getElementById('response')

let score = 0
let lastScore = [0]
let gameFrame = 0
let bg_x = -70
let bg_y = -280
let currentQuest
let count = 10
let countdown
let steps = 6
let isDrawFruits = true
let isLore = false
let loreCounter = 0
let drawCow = false
let drawMonshroom = false
let isAnimate = false
let cow2 = true

/// images 
const bg = new Image()
bg.src = 'images/bg.png'

const item = new Image()
item.src = 'images/items.png'

const cow = new Image()
cow.src = 'images/cow.png'
///

let matrix = getMatrix()
let matrix2 = matrix.map(innerArray => [...innerArray])
function drawFruits() {
    for (let i = 0; i < 7; i++) {
        if (i != 0) {
            drawLine(
                550, 70 * i + 80,
                550 + 490, 70 * i + 80
            )
        }
            for (let j = 0; j < 7; j++) {
                if (matrix2[i][j] != 2 && isDrawFruits)
                ctx.drawImage(item,
                    16 * (matrix2[i][j] + 5), 0,
                    16, 16,
                    70 * i + 550, 70 * j + 80,
                    70, 70
                )
                if (j != 0) {
                    drawLine(
                    70 * j + 550,85,
                    70 * j + 550,80 + 480
                )
                }
                
            }
    }
}

class Player {
    constructor() {
        this.image = new Image()
        this.image.src = 'images/move.png'
        this.position = []
        this.pos = 1
        this.x = 50
        this.y = 430
        this.speed = 70
        this.isGameOn = false
        this.sleep = false
        this.isQuestion = false
        this.moveIndex = 1
    }

    draw() {
        ctx.drawImage(this.image, 
            16 * this.moveIndex, 16 * this.pos,
            16, 16,
            this.x, this.y,
            70, 70
        )
    }

    animatePlayer() {
        if (isAnimate && player.moveIndex <= 6) {
            player.moveIndex += 3;
        } 
        else {
            player.moveIndex = 1;
        }
    }

    moveViewer() {
        window.addEventListener('keydown', (event) => {
            if (!this.sleep && steps > 0 && !this.isQuestion) {
                if ((event.key === 'w' || event.key === 'ArrowUp') && this.y != 80) {
                    this.y -= this.speed;
                    this.sleeper()
                    this.pos = 4
                    steps--
                    this.checkCollison()
                }
                if ((event.key === 's' || event.key === 'ArrowDown') && this.y != 500) {
                    this.y += this.speed;
                    this.sleeper()
                    this.pos = 1
                    steps--
                    this.checkCollison()
                }
                if ((event.key === 'a' || event.key === 'ArrowLeft') && this.x != 550) {
                    this.x -= this.speed;
                    this.sleeper()
                    this.pos = 7
                    steps--
                    this.checkCollison()
                }
                if ((event.key === 'd' || event.key === 'ArrowRight') && this.x != 970) {
                    this.x += this.speed;
                    this.sleeper()
                    this.pos = 10
                    steps--
                    this.checkCollison()
                }
            }
        });
    }

    sleeper() {
        this.sleep = true
        setTimeout(() => this.sleep = false, 200)
    }

    getStartPos() {
        let isAdd = true
        if (!this.isGameOn && isAdd) {
            for (let i = 0; i < 7; i++) {
                for (let j = 0; j < 7; j++) {
                    window.addEventListener('click', (event) => {
                        const rect = canvas.getBoundingClientRect();
                        const x = event.clientX - rect.left;
                        const y = event.clientY - rect.top;
                        if (x > 70 * i + 550 && x < 70 * i + 620 && y > 70 * j + 80 && y < 70 * j + 150) {
                            if (!this.isGameOn ) {
                                player.x = 70 * i + 550
                                player.y = 70 * j + 80
                                this.position = [i, j]
                            }
                        }
                    })
                } 
                if (i == 7) isAdd = false
            }
        }
    }

    checkCollison() {
        for (let i = 0; i < 7; i++) {
            for (let j = 0; j < 7; j++) {
                if (this.x == 70 * i + 550 && this.y == 70 * j + 80) {
                    if (matrix2[i][j] == 1) {
                        score = score + 1
                        matrix2[i][j] = 2
                        break
                    }
                    if (matrix2[i][j] == 0) {
                        score = score + 1
                        matrix2[i][j] = 2
                        showQuest()
                        break
                    }
                }
            }
        }
    }

    update() {
        this.moveViewer()
        if (steps != 6) {
            this.isGameOn = true 
            matrix2[this.position[0]][this.position[1]] = 2
        }
        if (isAnimate) { this.animatePlayer() }
    }
}
player = new Player()

function addResponse(responseText) {
    response.innerHTML = responseText
    response.style.display = 'block'
    setTimeout(() => {
        response.innerHTML = ''
        response.style.display = 'none'
    }, 3000)
}

function loreResponse(responseText) {
    response.innerHTML = responseText
    response.style.display = 'block'
}

response.addEventListener('click', function() {
    response.style.display = 'none'
    loreCounter += 1
    console.log(loreCounter)
})

function badAwser(){
    let num = Math.floor(Math.random() * 3)
    if (num == 0) {
        steps--
        addResponse('Megszédültél a gombától (minusz 1 pont).')
    }
    else if (num == 1) {
        isDrawFruits = false
        previusStep = steps
        setInterval(() => {
            if (previusStep > steps) {
                isDrawFruits = true
            }
        }, 500)
        addResponse('Ideiglenesen megvakultál a gombától, te kis butus ne vegyél mindent a szádba \n(következő lépésig nem látod a mezőket).')
    }
    else if (num == 2) {
        matrix2.forEach(out => {
            let rand = Math.floor(Math.random() * 7 + 1) 
            out[rand] = 2
            addResponse('Sietnem kell sorba rohadnak el a gombák.')
        })
    }
}

function goodAwser(){
    let num = Math.floor(Math.random() * 4)
    if (num == 0 && steps < 5) {
        steps++
        score++
        addResponse('Azta Ilyen finomat még nem ettem!! (+1 pont, +1 lépés).')
    }
    else if (num == 1) {
        player.x = Math.floor(Math.random() * 7) * 70 + 550
        player.y = Math.floor(Math.random() * 7) * 70 + 80
        addResponse('Huu de jól laktam (teleportálas).')
    }
    else if (num == 2) {
        matrix2.forEach(out => {
            let rand = Math.floor(Math.random() * 7 + 1) 
            out[rand] = 0
            addResponse('Azta új gombák nöttek ki.')
        })
    }
    else {
        addResponse('Finom volt (nem történt semmi.)')
    }

}

function showQuest(){
    currentQuest = questions[Math.floor(Math.random() * 49) + 1]
    questBox.style.display = 'block'
    quest.innerHTML = currentQuest.quest
    questButton1.innerHTML = currentQuest.awser1
    questButton2.innerHTML = currentQuest.awser2
    player.isQuestion = true
    count = 4
    countdown = setInterval(() => {
        if (count > 0) {
            count--
            questTimer.innerHTML = count
        }
        else {
            player.isQuestion = false
            questBox.style.display = 'none'
            steps--
            addResponse('Tul sokáig álltál és elfáradtál (minusz 1 pont).')
            clearInterval(countdown)
        }
    }, 1000)
    count = 4
}

function IsCorrectAwser(awserID) {
    if (awserID == currentQuest.correct) {
        if (steps < 5) { steps++ }
        player.isQuestion = false
        questBox.style.display = 'none'
        goodAwser()
    }
    else {
        badAwser()
        player.isQuestion = false
        questBox.style.display = 'none'
    }
    clearInterval(countdown)
}

function drawLine(sx, sy, tx, ty) {
    ctx.beginPath()
    ctx.moveTo(sx, sy)
    ctx.lineTo(tx, ty)
    ctx.strokeStyle = '#74a872'
    ctx.stroke()
}

function getMatrix(){
    let matrix = []
    for (let i = 0; i < 7; i++) {
        let matrix2 = []
        for (let j = 0; j < 7; j++) {
            matrix2.push(Math.floor(Math.random() * 3))
        }
        matrix.push(matrix2)
    }
    return matrix
}

function walk(){
    setTimeout(() => {player.getStartPos();player.x = 270;player.y = 430}, 10)
    bg_x = -600
    gameLoop()
}

function storyAndPlay(){
    isLore = true
    gameLoop()
}

function menuFunc(){
    play.addEventListener('click', function() {
        menu.style.display = 'none'
        walk()
    })
    story.addEventListener('click', function() {
        menu.style.display = 'none'
        storyAndPlay()
    })
}

function drawScore() {
    ctx.font = '30px Arial';
    ctx.fillStyle = 'black';
    if (steps != 6) {
        ctx.fillText('pont: ' + score, 180, 210)
        ctx.fillText('lépés: ' + steps, 180, 245)
        ctx.fillText('max pont: ' + Math.max(...lastScore), 180, 285)
    }
    else {
        ctx.font = '20px Arial';
        ctx.fillText('Válassz egy mezőt a kurzor segítségével.', 20, 210)
        ctx.fillText('Mozogj az kezdéshez (w,a,s,d).', 20, 240)
    }
}


function draw() {
    ctx.imageSmoothingEnabled = false;
    ctx.drawImage(
        bg, 
        350, 120,
        400, 240,
        bg_x, bg_y,
        1800, 1050
    )
    if (!isLore) {
        drawScore()
        drawFruits()
    }
    if (drawCow) {
        ctx.drawImage(cow, 300, 200, 90, 70)
        if (cow2) { ctx.drawImage(cow, 220, 200, 90, 70) }
    }
    if (drawMonshroom) {
        ctx.drawImage(item,
            16 * 5, 0,
            16, 16,
            360, 430,
            70, 70
        )
    }
    
    player.draw()
}

function showEndScreen(){
    end.style.display = 'block'
}

newGame.addEventListener('click', function() {
    end.style.display = 'none'
    steps = 6
    player.isGameOn = false
    player.pos = 1
    matrix2 = matrix.map(innerArray => [...innerArray])
    lastScore.push(score)
    score = 0
    isDrawFruits = true
    setTimeout(() => {player.getStartPos();player.x = 270;player.y = 430}, 10)
    bg_x = -600
})

newGameNew.addEventListener('click', function() {
    end.style.display = 'none'
    steps = 6
    player.isGameOn = false
    player.pos = 1
    matrix = getMatrix()
    matrix2 = matrix.map(innerArray => [...innerArray])
    lastScore.push(score)
    score = 0
    isDrawFruits = true
    setTimeout(() => {player.getStartPos();player.x = 270;player.y = 430}, 10)
    bg_x = -600
})

function update() {
    player.update()
    if (steps <= 0 && !player.isQuestion) {showEndScreen();lastPoint.innerHTML = 'Az elért pontod: ' + score}
    if (isLore) { lore() }
}

function gameLoop(){
    ctx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT)
    draw()
    if (gameFrame % 5 == 0) {update()}
    gameFrame++
    requestAnimationFrame(gameLoop)
}

function MovePlayer(x, y, direct) { // 50 430
    const moveing = setInterval(() => {
        if (player.x != x) player.x += 1 * direct
        else if (player.y != y) player.y += direct
        else {clearInterval(moveing); isAnimate = false, player.moveIndex = 1}
    }, 10)
}

function lore() {
    switch (loreCounter) {
        case 0:
            loreResponse('Katttingass a dobozra a folytatásért.')
            break;
        case 1:
            loreResponse('Szia a neves Szőr Bobi. Egy szigeten élek.')
            player.pos = 10
            isAnimate = true
            MovePlayer(300, 430, 1)
            break;
        case 2:
            player.pos = 4
            loreResponse('Jelenleg földműveléssel foglalkozom. Régebben voltak teheneim is.')
            drawCow = true
            break;
        case 3:
            player.pos = 1
            loreResponse('Csak voltak. Az eggyik vizbefulladt.')
            cow2 = false
            break;
        case 4:
            loreResponse('A másikba belecsapott a villám. ')
            drawCow = false
            break;
        case 5:
            loreResponse('Azota földművaléssel foglalkozom.')
            player.pos = 10
            isAnimate = true
            const timer1 = setInterval(() => {
                if (bg_x > -600) bg_x -= 1
                else {clearInterval(timer1); isAnimate = false; player.moveIndex = 1}
            }, 1)
            break;
        case 6:
            loreResponse('Egy csirkeólban élek, és buzát termesztek.')
            player.pos = 4
            isAnimate = true
            const timer2 = setInterval(() => {
                if (bg_y < -50) bg_y += 1
                else {
                    clearInterval(timer2) 
                    isAnimate = false
                    player.moveIndex = 1
                }
            }, 10)
            break;
        case 7:
            player.pos = 1
            loreResponse('Nem valami izgalmas itt lenni, egyszer meglátogatott egy tengeri malac és megettem.')
            break;
        case 8:
            isAnimate = true
            player.pos = 7
            const timer3 = setInterval(() => {
                if (bg_x != -10) bg_x += 1
                else {
                    clearInterval(timer3) 
                    isAnimate = false
                    player.pos = 1
                    player.moveIndex = 1
                }
            }, 10)
            loreResponse('Itt van a kertem nem valami szép.')
            break;
        case 9:
            loreResponse('Van egy másik kertem is amin alig nött a búza ezért az egyik évben nem vetettem be.')
            break;
        case 10:
            loreResponse('És kinött egy csomó gomba.')
            break;
        case 11:
            loreResponse('Megyek és meg is mutatom.')
            isAnimate = true
            player.pos = 10
            let next1 = false
            let next2 = false
            const timer4 = setInterval(() => {
                if (bg_x > -600) bg_x -= 1
                else {
                    clearInterval(timer4) 
                    player.pos = 1
                    next1 = true
                }
            }, 10)

            
            const timer5 = setInterval(() => {
                if (next1) {
                    if (bg_y > -300) bg_y -= 1
                    else {
                        clearInterval(timer5) 
                        next2 = true
                        next1 = false
                        player.pos = 10
                    }
                }
            }, 10)
            const timer6 = setInterval(() => {
                if (next2) {
                    if (bg_x > -800) bg_x -= 1
                    else {
                        clearInterval(timer6) 
                        next2 = false
                        player.pos = 1
                        isAnimate = false
                        player.moveIndex = 1
                    }
                }
            }, 10)
            break;
        case 12:
            loreResponse('Amikor gombát szedek minig azt csinálom hogy ha 2 gomba van egymás mellett megeszem a kissebbiket.')
            drawMonshroom = true
            break;
        case 13:
            loreResponse('Ezek a gombak nem halálosak, de valamelyik mérgező.')
            break;
        case 14:
            loreResponse('Néha csak jóllakok néha megvakulok tőlük ideiglenesen.')
            drawMonshroom = false
            break;
        case 15:
            loreResponse('Vannak olyan gombák is amelyek mellett nem nő gomba azokat csak elrakom késöbbre.')
            break;
        case 16:
            loreResponse('De nem lopom tovább a napot szedjük le a gombákat (kattincs a folytatásért)')
            player.pos = 7
            const timer7 = setInterval(() => {
                if (bg_x < -600) bg_x += 1
                else {
                    clearInterval(timer7) 
                    player.pos = 1
                    isAnimate = false
                    bg_y = -280
                }
            }, 10)
            break;
        case 17:
            isLore = false
            player.isGameOn = false
            player.getStartPos()
            break;

    }
}
menuFunc()