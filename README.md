# Railway Management System

A comprehensive C++ desktop application for managing railway operations including ticket booking, train scheduling, and administrative tasks. Built with SFML for the graphical user interface.

## Features

### For Passengers
- **User Authentication** - Secure login and registration system
- **Ticket Booking** - Book tickets by selecting origin, destination, and preferred train class
- **Ticket Cancellation** - View and cancel booked tickets
- **Train Classes** - Choose from Business, Economy, and Executive class tickets with different pricing

### For Administrators
- **Station Management** - Add, view, and remove railway stations
- **Track Management** - Define routes between stations with distance tracking
- **Train Management** - Add and manage different train services
- **Schedule Management** - Set up train schedules with arrival and departure times
- **Pricing Control** - Configure ticket prices for each class type

### UI Features
- **Dark/Light Mode** - Toggle between light and dark themes
- **Scrollable Lists** - Navigate through long lists of stations, trains, and bookings
- **Password Visibility** - Show/hide password fields

## Prerequisites

- **Compiler**: MinGW-w64 with g++
- **Graphics Library**: SFML 2.5+ (Simple and Fast Multimedia Library)
- **Operating System**: Windows (uses Windows-specific libraries)

## Project Structure

```
RailwayManagement/
├── main.cpp              # Application entry point
├── backend.cpp           # Core business logic and data management
├── button.hpp            # UI button and input box components
├── pages.hpp             # Page rendering and navigation
├── Makefile              # Build configuration
├── src/include/SFML/     # SFML header files
├── Font/                 # Application fonts (Times.ttf, arial.ttf)
├── Images/               # UI icons and graphics
│   ├── Icon0.png, Icon1.png
│   ├── book_tickets.png
│   ├── cancel_tickets.png
│   ├── details.png
│   ├── done.png
│   ├── delete.png
│   ├── hide_icon.png
│   ├── show_icon.png
│   └── invert0.png, invert1.png
└── *.dll                 # SFML runtime libraries
```

## Building the Project

### Using Make
```bash
make
```

### Manual Compilation
```bash
g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lsfml-main -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
```

## Usage

1. **Launch the application** by running `main.exe`
2. **Login** with existing credentials or create a new account
3. **Default Admin Login**: Check user.txt for admin credentials (if exists)
4. **Book Tickets**: Select boarding station, destination, and train class
5. **Manage System** (Admin only): Access station, track, train, and schedule management

## Data Files

The application uses the following text files for data persistence:

- `user.txt` - User credentials and admin status
- `station.txt` - List of railway stations
- `tracks.txt` - Route information between stations
- `trains.txt` - Train names and class types
- `booking.txt` - Passenger booking records
- `business.txt`, `economy.txt`, `executive.txt` - Ticket prices
- `[TrainName].txt` - Individual train schedules

## Architecture

### Class Hierarchy

```
users                    - User management (login, registration)
tracks                   - Route/track data management
  └── station            - Station operations and track management
trains                   - Base train class
  ├── train_business     - Business class trains
  ├── train_economy      - Economy class trains
  └── train_executive    - Executive class trains
train_stop               - Individual station stops
train_schedule           - Train timetable management
passanger_booking        - Booking operations
```

### UI Components

- **Button** - Clickable buttons with text labels
- **Input_box** - Text input fields with password masking support
- **Text_box** - Display text containers

## Keyboard Shortcuts

- **Mouse Wheel** - Scroll through lists
- **Click** - Select buttons and input fields
- **Backspace** - Delete characters in input fields
- **Theme Toggle** - Click the invert icon (top-right corner)

## Notes

- The application stores all data in plain text files
- Passwords are not encrypted - for demonstration purposes only
- Ensure all image and font resources are in their respective folders
- SFML DLL files must be in the same directory as the executable

## Dependencies

- SFML 2.5 or later
- MinGW-w64 compiler
- Windows operating system

## License

This project is created for educational purposes.

## Author

Railway Management System - C++ OOP Project
