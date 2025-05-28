# 🃏 Blackjack Console Game in C++

A simple terminal-based Blackjack game written in C++, featuring user accounts, a betting system, and win streak tracking.

## Features

- User registration with token-based betting
- Balance saving between game sessions
- Standard Blackjack rules (dealer hits until 17)
- Win streak counter
- Optional Double Down move
- Console-based user interface

### Persistent Account

The game stores your account info and balance between sessions using file I/O. Make sure you have write permissions in the folder you're running it from.

## How It Works

After launching the game, the player can register an account and place bets using tokens. Both the player and dealer receive two cards. The game follows classic Blackjack rules where the goal is to get as close to 21 as possible without going over. Players can choose to:

- `1` Stand
- `2` Hit
- `3` Double Down (if eligible)

The dealer automatically draws until reaching at least 17. The winner is determined based on hand values, and the token balance is updated accordingly.

## Notes

- Designed for Windows (uses `SetConsoleOutputCP`, `Sleep`, and `system("pause")`)
- Built for educational purposes
- No splitting or insurance features implemented yet