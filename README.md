![](https://i.imgur.com/yH8duF0.png)

-- Instructions -- 
The game that has been developed is Connect Four. The game comes with a couple of additional game modes such as Pop-Out & Connect Five.
In this section, we will explain how the clients are able to setup a game and connect with each other or play against the A.I. 
To start off have one player launch the server. Once the server has been launched the host should than provide the oponent their IP. This would allow for the players to connect to the lobby. Once the players have both inserted their names and the IP(host not required to). They will be send to the lobby screen if a connection was made. 
Inside the lobby scene the players are able to change their chips colour and select what gamemode they would like to play. Once both players have readied up then they will be taken into the game scene. Inside the game scene the players will both have a turn each, where they are able to place a chip into the board.Achieving a line of chips equal to the defined number to win (usually 4) in horizontal, vertical or diagonal directions would trigger the win condition depending on which player has achieved it. Once one of the players has won, they will be taken to the win scene. In the win scene the players are able to exit to the title screen, replay the game or return to the lobby to make changes.
If only one player is connected and they ready-up, than they will be facing the A.I. Once the A.I defeats the player or vice versa the same scenario would be executed. 

# Brief 

> The knock on the door echoed through the empty rooms. Where furniture once
sat, now only imprints in the carpet and silhouettes of dust remained. The
moment they'd been fearing had finally come. Things had been tough and forced
their hands. The tax bill had been unexpected and insanely high, but the real
cherry on the top was the double rates the utilities companies had charged. It
had become all too clear now that misstep after misstep had led to this moment.
Maybe they should have sold when they had the chance? The door knocked again. It
was time! Foreclosure was upon them, the cost of playing laid bare. The cost of
Monopoly!

**There's nothing boring about board games!**

For this assignment you will need to recreate a networked version of a board
game. You are free to choose whichever board game you desire, but it must be
turn-based and support 2+ players. The assignment is to be undertaken in pairs
and mandates the use of the ASGE engine alongside the kissnet network library.
*You can of course improve upon any perceived weaknesses in the original, or
alter mechanics to make the digital version your own.*

![](https://www.gannett-cdn.com/presto/2019/08/23/PPES/58b53966-1398-4bdd-90af-048fc925bf2b-store2.jpg)

Project Layout
------
* apps
  * ASGEGame: the game client and OpenGL Window
    * data: used for assets and game deployment
    * resources: used for icons 
  * ASGEServer: the dedicated server i.e. no window
    * data: used for assets and game deployment
  
* extern
  * important build scripts and other submodules
  * to update the submodules
    * `git pull --recurse-submodules`
    * `git submodule update --init --remote --recursive`
  
* include:
  * ASGENetLib: header files belonging to your game 
* src 
  * **reusable game components go here i.e. dice, animated sprite, game panel, game state  etc** 
  * The corresponding hpp files go in the include directory
   
   
Static Analysis
------
CLion will automatically apply clang-tidy settings to your project.
Just make sure to resolve any warnings it flags to prevent the CI checks
from failing. Cppcheck support has also been enabled if you've installed
it locally on the machine. A Cppcheck build target will be shown if the
exe was located. You can ignore any errors relating to third-party libraries. 

GameData
------
In order to access your game data from the game, you need to ensure that the +GD target has been run. You need to run this when you've modified the contents of your Data folder. 
