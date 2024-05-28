# flattops

A naval battle game made in C++ with raylib, inspired by the flattops game on TempleOS.

## Installation

Clone the repository using the following command:

```sh
git clone https://github.com/hugo-russeil/flattops.git
```

Once cloned, navigate into the repository directory and use the provided Makefile to compile the game:

```sh
cd flattops
make
```

Ensure you have raylib installed on your system. If not, you can check out [raylib's website](https://www.raylib.com/).

## Features

This version of flattops includes several exciting features:

- **Ship Types**: 
  - **Aircraft Carrier (CV)**
  - **Battleship (BB)**
  - **Battlecruiser (BC)**
  - **Light Cruiser (CL)**
  - **Destroyer (DD)**
  - **Submarine (SS)**
  
- **Battleground**: The game takes place on a vast, open water setting, providing a realistic naval combat environment.

- **Gameplay Mechanics**: 
  - **Ship Placement Phase**: Strategically place your ships at the beginning of the game.
  - **Ship Selection**: Select ships individually or multiple ships at once using shift-click. Group selected ships for easy management.
  - **Movement and Targeting**: Assign target destinations to ships. Ships will automatically engage nearby enemies.
  - **Carrier and Bombers**: Manage aircraft carriers and control bombers
  - **Group Management**: Create groups of ships for coordinated attacks.
  - **Control Commands**: Use specific commands to get more control over units actions.

- **AI**: Currently, there is no AI component for enemy ships. This may be added in the future.

- **Game Modes**: There is currently only one game mode available.

- **Multiplayer**: The game is currently single-player only. Future versions may include multiplayer functionality.

## Usage

Once compiled, the game runs like any other program. At the beginning, there is a phase where you can place your ships. The controls are as follows:

- **Left Click** a ship to select it.
- **Right Click** to give a selected ship a target destination.
- Ships shoot at close enemies on their own.
- **H**: Stop a selected ship.
- **Shift + Click**: Select multiple ships.
- **G**: Group selected ships for easy selection later.
- **Number Keys**: Select groups you have created.
- **B**: When selecting a carrier, select the bombers group on board.
- **Right Click**: Assign bombers a target enemy ship.
- **H**: Order planes back to the carrier.
- **K**: Order a "one way trip" for planes.

## Precompiled Binaries

Not yet available, the project is still a work in progress.

## Contributing

While contributions are not expected, feel free to submit pull requests if you have any improvements or suggestions. My aim is to learn and I am open to any constructive feedback.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
