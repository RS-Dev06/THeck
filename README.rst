===================
TMenu Game Cheat
===================

.. image:: https://img.shields.io/badge/Version-1.0-blue
   :alt: Version 1.0
.. image:: https://img.shields.io/badge/License-Private-red
   :alt: License
.. image:: https://img.shields.io/badge/Platform-Windows-green
   :alt: Platform

|

.. raw:: html

   <img src="assets/icon.png" alt="TMenu Logo" style="width:40px;vertical-align:middle"> <strong>TMenu</strong> is a powerful game memory manipulation tool built with ImGui and DirectX9, allowing you to enhance your gaming experience through various memory modifications.

.. contents:: Table of Contents   :class: inline-image
   :depth: 2
   :local:**TMenu** is a powerful game memory manipulation tool built with ImGui and DirectX9, allowing you to enhance your gaming experience through various memory modifications.
   :backlinks: none
.. contents:: Table of Contents
|

------------nks: none
Key Features
------------|

.. image:: assets/features.gif------------
   :alt: Features Demo
   :align: center
   :width: 600px
.. image:: assets/features.gif
|

✅ **Memory Manipulation**
   - Modify health and mana values
   - Freeze values at specific points|
   - Allow values to only increase (never decrease)
✅ **Memory Manipulation**
✅ **Player Modifications**na values
   - Ghost mode (walk through walls/objects)nts
   - Teleportation system with position savingever decrease)
   - Defense and life regeneration adjustment
✅ **Player Modifications**
✅ **Inventory Manipulation**ugh walls/objects)
   - Set item amounts in inventoryng
   - Modify selected item properties

✅ **Authentication System**✅ **Inventory Manipulation**
   - Secure login with KeyAuth integrationentory
   - User management with session trackinges

✅ **User Experience**✅ **Authentication System**
   - Fully customizable overlay opacityuth integration
   - Intuitive GUI with color-coded values
   - Keyboard shortcuts for quick toggling
✅ **User Experience**
------------le overlay opacity
Installationues
------------

Prerequisites------------
============

- Windows OS
- Administrator privilegesPrerequisites
- Target game must be running
- Microsoft Visual Studio 2019 or newer
- DirectX SDK- Windows OS
- Windows SDK 10.0 or newertor privileges
- C++ development toolsing
9 or newer
Setup
===== 10.0 or newer

1. Download the latest release from the releases page
2. Extract all files to a folder of your choiceSetup
3. Run ``MenuProtoOne.exe`` as administrator
4. Enter your login credentials when prompted
1. Download the latest release from the releases page
.. code-block:: bash

   # Alternative method (for developers)d
   # Build from source using Visual Studio
   gh repo clone RS-Dev06/THeck.. code-block:: bash
   cd THeck
   # Open MenuProtoOne.sln in Visual Studio and build   # Alternative method (for developers)
io
-----------------
Build From Source
-----------------enuProtoOne.sln in Visual Studio and build

Development Environment Setup-----------------
============================

1. **Install Required Software:**
Development Environment Setup
   - Visual Studio 2019 or newer with C++ desktop development workload
   - DirectX SDK (June 2010 or newer)
   - Windows 10 SDK1. **Install Required Software:**

2. **Clone the Repository:**   - Visual Studio 2019 or newer with C++ desktop development workload

   .. code-block:: bash

      gh repo clone RS-Dev06/THeck2. **Clone the Repository:**
      cd THeck
   .. code-block:: bash
Building the Project
===================      gh repo clone RS-Dev06/THeck

**Using Visual Studio IDE:**
Building the Project
1. Open ``MenuProtoOne.sln`` in Visual Studio
2. Select your desired configuration:
   - ``Debug`` - For development with debugging symbols**Using Visual Studio IDE:**
   - ``Release`` - For optimized performance build
3. Select ``x64`` as the target platform1. Open ``MenuProtoOne.sln`` in Visual Studio
4. Build the solution by pressing ``F7`` or selecting ``Build > Build Solution``
5. The output executable will be created in either: debugging symbols
   - ``x64/Debug/`` for debug builds
   - ``x64/Release/`` for release builds
 or selecting ``Build > Build Solution``
**Using Command Line:**

.. code-block:: bashilds

   # Navigate to project directory**Using Command Line:**
   cd path\to\THeck
   .. code-block:: bash
   # For Debug build
   msbuild MenuProtoOne.sln /p:Configuration=Debug /p:Platform=x64   # Navigate to project directory
   
   # For Release build
   msbuild MenuProtoOne.sln /p:Configuration=Release /p:Platform=x64# For Debug build
One.sln /p:Configuration=Debug /p:Platform=x64
Dependencies
===========# For Release build
e.sln /p:Configuration=Release /p:Platform=x64
The project has the following dependencies that are included in the repository:
Dependencies
- **Dear ImGui** - Included in ``ImGui/`` directory
- **libcurl** - For network communication, static library in ``Cheat/libcurl.lib``
- **KeyAuth** - Authentication system in ``Cheat/auth.hpp`` and ``Cheat/library_x64.lib``The project has the following dependencies that are included in the repository:

Common Build Issues- **Dear ImGui** - Included in ``ImGui/`` directory
==================ibrary in ``Cheat/libcurl.lib``
4.lib``
1. **DirectX SDK Missing:**
   Common Build Issues
   If you encounter errors about missing DirectX headers or libraries:

   .. code-block:: text1. **DirectX SDK Missing:**

      Error: Cannot open include file: 'd3d9.h': No such file or directoryIf you encounter errors about missing DirectX headers or libraries:

   Ensure the DirectX SDK is properly installed and the paths are configured in Visual Studio:   .. code-block:: text
   - Go to ``Project > Properties > VC++ Directories``
   - Add the DirectX SDK include and library paths      Error: Cannot open include file: 'd3d9.h': No such file or directory

2. **Library Not Found:**   Ensure the DirectX SDK is properly installed and the paths are configured in Visual Studio:

   .. code-block:: text

      Error: Cannot find library 'libcurl.lib' or 'library_x64.lib'2. **Library Not Found:**

   The project is configured to look for these libraries in specific paths. Verify that:   .. code-block:: text
   - The libraries are present in the ``Cheat/`` directory
   - The project properties correctly reference these paths      Error: Cannot find library 'libcurl.lib' or 'library_x64.lib'

3. **Windows SDK Version:**   The project is configured to look for these libraries in specific paths. Verify that:

   If you encounter Windows SDK version mismatches:s
   - Go to ``Project > Properties > General``
   - Update the Windows SDK Version to match your installed version3. **Windows SDK Version:**

Customizing the Build   If you encounter Windows SDK version mismatches:
====================
your installed version
To modify the build configuration:
Customizing the Build
1. **Change Target Game:**
   
   - Edit memory addresses and offsets in ``Cheat/MemoryAccess.cpp``To modify the build configuration:
   - Update process name detection in ``MemEdit::MemEdit()`` constructor
1. **Change Target Game:**
2. **Disable Features:**
   - Edit memory addresses and offsets in ``Cheat/MemoryAccess.cpp``
   - In ``Cheat/gui.cpp``, modify the ``Render`` function to remove unwanted featuresctor
   - Comment out corresponding sections in ``Cheat/MemoryAccess.cpp``
2. **Disable Features:**
3. **Change UI Appearance:**
   - In ``Cheat/gui.cpp``, modify the ``Render`` function to remove unwanted features
   - In ``gui.cpp``, modify the ``CreateImGui`` function
   - Adjust color schemes with ``ImGui::StyleColorsClassic()`` or other style functions
   - Modify window dimensions in ``gui.h`` by changing the ``WIDTH`` and ``HEIGHT`` constants3. **Change UI Appearance:**

------ In ``gui.cpp``, modify the ``CreateImGui`` function
Usageic()`` or other style functions
-----stants

Basic Controls-----
=============

- **INSERT** - Toggle overlay visibility
- **END** - Exit application completelyBasic Controls
- **HOME** - Reset all modifications to default values

.. image:: assets/keyboardDemo.gif- **INSERT** - Toggle overlay visibility
   :alt: Keyboard Controls Demo
   :align: center default values
   :width: 600px
.. image:: assets/keyboardDemo.gif
|

Authentication
=============
|
.. image:: assets/login.gif
   :alt: Login Screen DemoAuthentication
   :align: center
   :width: 600px
.. image:: assets/login.gif
|

1. Launch the application
2. Enter your username and password
3. Click "Login"|
4. Upon successful authentication, the cheat menu will appear
1. Launch the application
Memory Manipulationd password
==================
ul authentication, the cheat menu will appear
.. image:: assets/memory.gif
   :alt: Memory Manipulation DemoMemory Manipulation
   :align: center
   :width: 600px
.. image:: assets/memory.gif
| Demo

**Health Management:**

- **Freeze Health**: Maintains health at the current value|
  - Perfect for boss fights or difficult areas
  - Prevents any damage from affecting your character**Health Management:**
  - Automatically reapplies the value whenever the game attempts to change it
- **Freeze Health**: Maintains health at the current value
- **Freeze Health With Increase**: Allows health to only increase, never decrease
  - Lets you collect health power-ups and healing itemsaracter
  - Blocks all damage effectsme attempts to change it
  - Maintains maximum health during encounters
- **Freeze Health With Increase**: Allows health to only increase, never decrease
**Mana Management:**

- **Freeze Mana**: Maintains mana at the current valueduring encounters
  - Cast unlimited spells without depleting resources
  - Perfect for magic-heavy gameplay**Mana Management:**
  - Values are preserved between areas and loading screens
- **Freeze Mana**: Maintains mana at the current value
- **Freeze Mana With Increase**: Allows mana to only increase, never decrease
  - Collect mana boosts and power-ups
  - Cast spells without worrying about resource managementas and loading screens
  - Automatically resets to highest achieved value if decreased
- **Freeze Mana With Increase**: Allows mana to only increase, never decrease
Player Modifications
===================t resource management
eased
.. image:: assets/playerModification.gif
   :alt: Player Modifications DemoPlayer Modifications
   :align: center
   :width: 600px
.. image:: assets/playerModification.gif
|

**Ghost Mode:**

1. Check the "Ghost Mode" box to enable walking through objects|
   - Pass through walls, barriers, and obstacles
   - Access locked or restricted areas**Ghost Mode:**
   - Avoid environmental damage and traps
   - Explore out-of-bounds areas1. Check the "Ghost Mode" box to enable walking through objects

2. Uncheck to return to normal collision detection
aps
**Teleportation System:**

.. image:: assets/teleport.gif2. Uncheck to return to normal collision detection
   :alt: Teleportation System Demo
   :align: center**Teleportation System:**
   :width: 600px
.. image:: assets/teleport.gif
|Demo

1. Navigate to the desired location in-game
2. Click "Set Teleport Point" to save coordinates
   - Multiple points can be saved during a session|
   - Coordinates are displayed in real-time
   - Save points near difficult areas, bosses, or loot1. Navigate to the desired location in-game
inates
3. Use "Teleport To Point" to instantly return to saved locationn
   - Bypass long travel distances
   - Escape dangerous situationses, or loot
   - Return to farming spots quickly
3. Use "Teleport To Point" to instantly return to saved location
**Defense & Regeneration:**

.. image:: assets/statView.gifckly
   :alt: Defense and Regeneration Demo
   :align: center**Defense & Regeneration:**
   :width: 600px
.. image:: assets/statView.gif
|ion Demo

- View current defense values in real-time
- Monitor life regeneration rates
- Values update dynamically as gear changes or buffs apply|
- Color-coded stats for easier reading:
  - Green: Optimal values- View current defense values in real-time
  - Yellow: Average values
  - Red: Critical values needing attentionar changes or buffs apply

Inventory Management
===================s
eeding attention
.. image:: assets/inventory.gif
   :alt: Inventory Management DemoInventory Management
   :align: center
   :width: 600px
.. image:: assets/inventory.gif
|emo

**Slot Eleven Modification:**

1. Use the "SL Amount" slider to set desired quantity (1-100)|
   - Perfect for consumables like potions or ammunition
   - Easily set exact quantities needed**Slot Eleven Modification:**
   - Changes apply instantly in-game
1. Use the "SL Amount" slider to set desired quantity (1-100)
2. Click "Set Amount" to apply changes
   - Modifications persist through area transitions
   - Stack sizes beyond normal game limitations
   - Circumvent inventory restrictions
2. Click "Set Amount" to apply changes
**Mouse Item Manipulation:**a transitions

.. image:: assets/mouseInv.gif
   :alt: Mouse Item Manipulation Demo
   :align: center**Mouse Item Manipulation:**
   :width: 600px
.. image:: assets/mouseInv.gif
|on Demo

1. Use the "Mouse Item Amount" slider to set desired quantity (1-100)
   - Modify currently held or selected items
   - Adjust quantities on-the-fly during gameplay|
   - Perfect for active trading or crafting sessions
1. Use the "Mouse Item Amount" slider to set desired quantity (1-100)
2. Click "Set Mouse Amount" to apply changes
   - Changes reflect immediately on cursor itemeplay
   - Useful for duplicating rare or valuable itemsons
   - Great for crafting materials and stackable goods
2. Click "Set Mouse Amount" to apply changes
Interface Customizationtem
======================ems
ods
.. image:: assets/customization.gif
   :alt: Interface Customization DemoInterface Customization
   :align: center
   :width: 600px
.. image:: assets/customization.gif
|mo

**Window Opacity:**

1. Use the "Opacity" slider to adjust transparency (50-255)|
   - Lower values for minimal visual obstruction
   - Higher values for better readability**Window Opacity:**
   - Find the perfect balance for your playstyle
1. Use the "Opacity" slider to adjust transparency (50-255)
2. Toggle visibility quickly with INSERT key
   - Instantly hide the menu when needed
   - Return to previous opacity settings when toggled backaystyle
   - Perfect for screenshots or recording gameplay
2. Toggle visibility quickly with INSERT key
**Menu Positioning:**
 when toggled back
- Click and drag the top bar to reposition the menu
- Position saved between sessions
- Place anywhere on screen for optimal visibility**Menu Positioning:**
- Automatically adjusts to screen resolution
- Click and drag the top bar to reposition the menu
---------------
Troubleshootingtimal visibility
---------------

Common Issues---------------
============

**Application Won't Start:**
Common Issues
- Ensure you have administrator privileges
- Verify that the target game is running
- Check Windows Defender or antivirus is not blocking execution**Application Won't Start:**

**Authentication Failures:**- Ensure you have administrator privileges

- Verify correct username and password not blocking execution
- Check internet connection
- Contact administrator if access should be granted**Authentication Failures:**

**Memory Modifications Not Working:**- Verify correct username and password

- Game may have been updated, requiring pattern updatesaccess should be granted
- Anti-cheat systems may be interfering with memory access
- Restart both the game and TMenu**Memory Modifications Not Working:**

-------- Game may have been updated, requiring pattern updates
Supportess
-------

If you encounter any issues or have questions, please contact us through one of these channels:-------

- **Discord**: Join our server at `discord.gg/tmenu <https://discord.gg/tmenu>`_
- **Email**: support@tmenu.com
- **GitHub Issues**: For bug reports and feature requestsIf you encounter any issues or have questions, please contact us through one of these channels:

-------- **Discord**: Join our server at `discord.gg/tmenu <https://discord.gg/tmenu>`_
License
-------eports and feature requests

TMenu is proprietary software. Unauthorized distribution, modification, or reverse engineering is strictly prohibited.-------

Copyright © 2023 TMenu Development Team. All rights reserved.

----------------TMenu is proprietary software. Unauthorized distribution, modification, or reverse engineering is strictly prohibited.
Acknowledgements
----------------Copyright © 2023 TMenu Development Team. All rights reserved.

- **Dear ImGui** - Immediate mode GUI library----------------
- **KeyAuth** - Authentication system
- **DirectX 9** - Graphics API

.. warning::- **Dear ImGui** - Immediate mode GUI library

   This software is intended for educational purposes only. Use of this software may violate the terms of service of certain games. The developers are not responsible for any consequences resulting from the use of this software.