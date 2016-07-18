NAME: DEFAULT TYPE
DESCRIPTION: No description is available yet for this type
MASS_MAX: -1
MASS_MIN: 0
BLUE_MAX: 255
BLUE_MIN: 0
RED_MAX: 255
RED_MIN: 0
GREEN_MAX: 255
GREEN_MIN: 0
PARENT: System

NAME: Artificial object
DESCRIPTION: The product of an intentional human manufacture, often buildt whit metals
PARENT: NULL

NAME: Asteroid
DESCRIPTION: An asteroid is a minor planet that have a composition very similar to a terrestrial planet. Asteroid composed meanly by ice are called comets, some asteroids are comets that have lose the ice
PARENT: Minor planet

NAME: Binary asteroids
PARENT: Asteroid

NAME: Black hole
BLUE_MAX: 0
RED_MAX: 0
GREEN_MAX: 0
PARENT: Compact star

NAME: Brown Dwarf
PARENT: Celestial object

NAME: Carbon Planet
DESCRIPTION: A carbon planet is a planet that contein much much carbon, and a minor quantity of oxygen
PARENT: Planet

NAME: Cataclysmic variable star
PARENT: Star

NAME: Celestial object
DESCRIPTION: A celestial object is a natural object
PARENT: NULL

NAME: Chthonian planet
DESCRIPTION: A chtonian planet is a planet generated from the hydrodinamic escape of a Gas Giant atmosphere. The remaining metal and rocky core form this planet
PARENT: Planet

NAME: Chose a type
DESCRIPTION: for your new object
PARENT: Whitout parent

NAME: Comet
PARENT: Small body

NAME: Compact star
DESCRIPTION: A compact star is a star that is composed by esotic matter (like white dwarf, neutron star and others) or other objects like the Black Holes that we don't know of which matter are composed. All these objects have big mass but are small, having a very high density.
PARENT: Star

NAME: Contact binary
PARENT: Small body

NAME: Debris
DESCRIPTION: Debrises are spacecraft remaining, stages used and discarded that often travel in the spaces freely and sometimes falls onto some planet surface
PARENT: Spacecraft

NAME: Dwarf planet
PARENT: Minor planet

NAME: Earth analog
DESCRIPTION: An Earth analog is a terrestrial planet whit characteristich much similar to the Earth's characteristics
PARENT: Terrestrial planet

NAME: Gas giant
PARENT: Giant planet

NAME: Generic object
DESCRIPTION: We don't know the nature of a Generic object, so we call it generic
PARENT: System

NAME: Giant planet
PARENT: Planet

NAME: Helium planet
DESCRIPTION: An helium planet is a planet whit an atmosphere composly mainly by helium
PARENT: Planet

NAME: Hot Jupiter
DESCRIPTION: A Hot Neptune is a giant gas planet that is very similar to Neptune but is much hotter that it
PARENT: Gas giant

NAME: Hot Neptune
DESCRIPTION: A Hot Neptune is a giant gas planet that is very similar to Neptune but is much hotter that it
PARENT: Gas giant

NAME: Ice giant
PARENT: Giant planet

NAME: Iron planet
DESCRIPTION: An iron planet is a planet whit the core composed mainly of iron and whit mantle very little or whitout any mantle
PARENT: Planet

NAME: Lava planet
DESCRIPTION: A lava planet is a type of terrestrial planet whit the surface completely covered whit lava
PARENT: Terrestrial planet

NAME: Magnetar
DESCRIPTION: A magnetar is a Neutron star whit a very strong magnetic field
PARENT: Neutron star

NAME: Mega Earth
DESCRIPTION: A Mega Earth is a terrestrial planet ten or more times more massive than Earth, even more massive than super-Earths that are five to ten times more massive than Earth 
MASS_MIN: 29800000000000000000000
MASS_MAX: 60000000000000000000000
PARENT: Terrestrial planet

NAME: Meteroid
PARENT: Small body

NAME: Micrometeroid
PARENT: Meteroid

NAME: Mini-Neptune
PARENT: Planet

NAME: Minor planet
PARENT: Celestial object

NAME: Minor-planet moon
DESCRIPTION: Is a moon orbiting a minor planet
PARENT: Minor planet

NAME: Neutron star
DESCRIPTION: Description coming soon
PARENT: Compact star

NAME: Ocean planet
PARENT: Planet

NAME: Planet
DESCRIPTION: A planet is a celestial body that is rounded by its own gravity because is massive enought, has cleared its neightbouring region of planetesimal and doesn't have thermonuclear fusion into it for is mass
PARENT: Celestial object

NAME: Planetesimal
PARENT: Small body

NAME: Pulsar
PARENT: Neutron star

NAME: Rogue planet
DESCRIPTION: A rogue planet is a planet that orbit the galaxy directly, whitout take part of any solar system
PARENT: Planet

NAME: Small body
PARENT: Celestial object

NAME: Spacecraft
DESCRIPTION: Is a veicle, often built by metals, designed to "fly" in the space for various motivations: communications, exploring, colonization and transport
PARENT: Artificial object

NAME: Spaceplane
DESCRIPTION: Often winged, a spaceplane is a spacecraft designed only for manned flight. For example the Space Shuttle is a spaceplane
PARENT: Spacecraft

NAME: Star
PARENT: Celestial object

NAME: Sub-brown dwarf
PARENT: Brown dwarf

NAME: Super Earth
DESCRIPTION: A super Earth is a terrestrial planet massive two to five Earth masses, more massive terrestrial planet are called Mega Earth
MASS_MIN: 11000000000000000000000		
MASS_MAX: 29863000000000000000000
PARENT: Terrestrial planet

NAME: Terrestrial planet
DESCRIPTION: A terrestrial planet is a planet composed mainly by rock and metal.
PARENT: Planet

NAME: White dwarf
PARENT: Compact star

END OF FILE

NOTES:
- EVERY type must have a name and a parent
- Maximum mass -1 means whitout limit
- NAME must be the first element of a type, PARENT the last
- Please keep the alphabetical order
- Leave a blank line between two types and don't put blank lines between type's elements
- Don't write comments before the "END OF FILE"
