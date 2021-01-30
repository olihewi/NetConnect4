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
