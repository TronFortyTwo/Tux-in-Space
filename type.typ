################################################################################
# NOTES:
# - EVERY type must have a name and a parent
# - Maximum mass -1 means whitout limit
# - NAME must be the first element of a type, PARENT the last
# - Please keep the alphabetical order
# - to write comment, start the line whit '#'
#################################################################################
#################################################################################
# the default type is the base for all the other types, but isn't a real type	
#################################################################################
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
HUNTED: N
HUNTER: N
PRODUCT: Asteroid
PARENT: System

###############################################################################
# These are the real types. The information missing are taken 
# from the default type
###############################################################################
NAME: Artificial object
DESCRIPTION: The product of an intentional human manufacture, often buildt whit metals
HUNTED: Y
PRODUCT: Debris
PARENT: NULL

NAME: Asteroid
DESCRIPTION: An asteroid is a minor planet that have a composition very similar to a terrestrial planet. Asteroid composed meanly by ice are called comets, some asteroids are comets that have lose the ice
PRODUCT: Meteroid
PARENT: Minor planet

NAME: Black hole
DESCRIPTION: A so massive and dense body that even the light can't escape from it
MASS_MIN: 0.02177
BLUE_MAX: 0
RED_MAX: 0
GREEN_MAX: 0
PARENT: Compact star

NAME: Brown Dwarf
DESCRIPTION: A brown dwarf is a particular type of celestial object that are more massive than planets, but they don't have nuclear fusion in their core
MASS_MIN: 2.467647e25
MASS_MAX: 1.528552e26
PARENT: Celestial object

NAME: Carbon Planet
DESCRIPTION: A carbon planet is a planet that contein much much carbon, and a minor quantity of oxygen
PARENT: Planet

NAME: Celestial object
DESCRIPTION: A celestial object is a natural object
PARENT: NULL

NAME: Chthonian planet
DESCRIPTION: A chtonian planet is a planet generated from the hydrodinamic escape of a Gas Giant atmosphere. The remaining metal and rocky core form this planet
PARENT: Planet

NAME: Choose a type
DESCRIPTION: for your new object
PARENT: System

NAME: Comet
DESCRIPTION: A comet is an icy body composed of water and dust. When exposed to solar wind, some of it's mass sublime and behind him a 'tail' appears.
PRODUCT: Meteroid
PARENT: Small body

NAME: Compact star
DESCRIPTION: A compact star is a star that is composed by esotic matter (like white dwarf, neutron star and others) or other objects like the Black Holes that we don't know of which matter are composed. All these objects have big mass but are small, having a very high density.
PARENT: Star

NAME: Contact binary
PARENT: Small body

NAME: Debris
DESCRIPTION: Debrises are spacecraft remaining, stages used and discarded that often travel in the spaces freely and sometimes falls onto some planet surface
PRODUCT: Debris
PARENT: Spacecraft

NAME: Deep Space Kraken
DESCRIPTION: Terrifying enormous creature that destroy anything what encouter. No one survived his attacks to confirm his existent
HUNTER: Y
PARENT: Space Monster

NAME: Dwarf planet
DESCRIPTION: A dwarf planet is a planetary mass object enought massive to have an hydrostatic equilibrium, but not enought to clear the materials in the neightbouroud space
PARENT: Minor planet

NAME: Earth analog
DESCRIPTION: An Earth analog is a terrestrial planet whit characteristich much similar to the Earth's characteristics
PARENT: Terrestrial planet

NAME: Gas giant
MASS_MAX: 2.5e25
PARENT: Giant planet

NAME: Generic object
DESCRIPTION: We don't know the nature of a Generic object, so we call it generic
PARENT: System

NAME: Giant planet
MASS_MAX: 2.467647e25
PARENT: Planet

NAME: Helium planet
DESCRIPTION: An helium planet is a planet whit an atmosphere composly mainly by helium
PARENT: Planet

NAME: Ice giant
PARENT: Giant planet

NAME: Iron planet
DESCRIPTION: An iron planet is a planet whit the core composed mainly of iron and whit mantle very little or whitout any mantle
PARENT: Planet

NAME: Lava planet
DESCRIPTION: A lava planet is a type of terrestrial planet whit the surface completely covered whit lava
PARENT: Terrestrial planet

NAME: Leviatan
DESCRIPTION: Enormous dragon of the space, the information about him are few
HUNTER: Y
PARENT: Space Monster

NAME: Magnetar
DESCRIPTION: A magnetar is a Neutron star whit a very strong magnetic field
PARENT: Neutron star

NAME: Mega Earth
DESCRIPTION: A Mega Earth is a terrestrial planet ten or more times more massive than Earth, even more massive than super-Earths that are five to ten times more massive than Earth 
MASS_MIN: 298e20
MASS_MAX: 6e22
PARENT: Terrestrial planet

NAME: Meteroid
DESCRIPTION: A meteroid is a rocky fragment. Them are usually generated from the asteroids impacts or from the comet cores
PRODUCT: Micrometeroid
MASS_MAX: 1e5
MASS_MIN: 1e-11
PARENT: Small body

NAME: Micrometeroid
DESCRIPTION: A very little little meteroid
PRODUCT: Micrometeroid
PARENT: Meteroid

NAME: Mini-Neptune
MASS_MAX: 1e23
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
PRODUCT: Meteroid
PARENT: Small body

NAME: Pulsar
PARENT: Neutron star

NAME: Small body
PARENT: Celestial object

NAME: Space Monster
DESCRIPTION: As in the old times big and unknow creatures have terrorized for years the men of the sea, now space monsters' legends terrorize the men in our modern times. Are they real or are only a legend?
HUNTER: Y
PARENT: NULL

NAME: Spacecraft
DESCRIPTION: Is a veicle, often built by metals, designed to "fly" in the space for various motivations: communications, exploring, colonization and transport
HUNTED: Y
PRODUCT: Debris
PARENT: Artificial object

NAME: Spaceplane
DESCRIPTION: Often winged, a spaceplane is a spacecraft designed only for manned flight. For example the Space Shuttle is a spaceplane
HUNTED: Y
PRODUCT: Debris
PARENT: Spacecraft

NAME: Star
DESCRIPTION: A star is a celestial body that have termonuclear reaction inside it, for that shine of its own light. Stars have a mass between 0.08 and 200 Sun Masses. Lighter objects are called brown dwarfs, and they don't produce energy via nuclear fusion
MASS_MIN: 9241818
MASS_MAX: 3.97784e29
PARENT: Celestial object

NAME: Sub-brown dwarf
PARENT: Brown dwarf

NAME: Super Earth
DESCRIPTION: A super Earth is a terrestrial planet massive two to five Earth masses, more massive terrestrial planet are called Mega Earth
MASS_MIN: 11e21		
MASS_MAX: 29.863e21
PARENT: Terrestrial planet

NAME: Terrestrial planet
DESCRIPTION: A terrestrial planet is a planet composed mainly by rock and metal
PARENT: Planet

NAME: White dwarf
PARENT: Compact star

EOF
# (END OF FILE)
