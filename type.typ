########################################################################
# TYPE.TYP
# In this file are listed all the types and their attributes
# The program read this file in runtime, not in compile time, so this file
#  must be shipped whit the executable, or it will fail to launch
#
# READ CAREFULLY BEFORE EDIT THIS FILE:
# - every type must have a name and a parent
# - NAME must be the first element of a type, PARENT the last
# - please, use the indentation (using tabs)
# - to write comments, start a line with '#'
# - there is no official support yet for types that are either hunter AND hunted
########################################################################
########################################################################
# the Object type is the base for all other types
########################################################################
NAME: Object
DESCRIPTION: An object is a bunch of matter with mass, examples are the Sun and a cellphone
MASS MAX: INF
MASS MIN: 0
BLUE MAX: 255
BLUE MIN: 0
RED MAX: 255
RED MIN: 0
GREEN MAX: 255
GREEN MIN: 0
HUNTED: N
HUNTER: N
MERGE: Y
PRODUCT: Object
PARENT: Object

########################################################################

#############################
# ARTIFICIAL OBJECTS
#
NAME: Artificial object
DESCRIPTION: The product of an intentional human manifacture, often buildt with metals
HUNTED: Y
MERGE: N
PRODUCT: Debris
PARENT: Object

	NAME: Spacecraft
	DESCRIPTION: Is a veicle, often built with metals, designed to "fly" in the space for various motivations: communications, exploring, colonization and transport
	HUNTED: Y
	PRODUCT: Relict
	PARENT: Artificial object

		NAME: Debris
		DESCRIPTION: Debrises are spacecraft remaining, stages used and discarded that often travel in the spaces freely and sometimes falls onto some planet surface
		PRODUCT: Debris
		PARENT: Spacecraft

		NAME: Relict
		DESCRIPTION: A spacecraft destroyed or damaged floating the universe...
		HUNTED: N
		PRODUCT: Debris
		PARENT: Spacecraft
		
########################################################################
# CELESTIAL OBJECTS (BODY)
#
NAME: Celestial object
DESCRIPTION: A celestial object is a natural object
MERGE: Y
PARENT: Object

	NAME: Brown Dwarf
	DESCRIPTION: A brown dwarf is a particular type of celestial object that is more massive than a planet, but doesn't have nuclear fusion in its core
	MASS MAX: 1.528552e29
	MASS MIN: 2.467647e28
	PARENT: Celestial object
	
		NAME: Sub-brown dwarf
		DESCRIPTION: A particular type of Brown Dwarf smaller than a regular one
		PARENT: Brown Dwarf
	
	NAME: Small body
	PARENT: Celestial object

		NAME: Comet
		DESCRIPTION: A comet is an icy body composed of water and dust. When exposed to solar wind, some of it's water sublime and behind him a 'tail' appears.
		PRODUCT: Meteroid
		PARENT: Small body

		NAME: Contact binary
		PARENT: Small body

		NAME: Planetesimal
		PRODUCT: Meteroid
		PARENT: Small body

		NAME: Meteroid
		DESCRIPTION: A meteroid is a rocky fragment. Is usually generated from asteroid impacts or from comet cores
		MASS MAX: 1e8
		MASS MIN: 1e-14
		PRODUCT: Micrometeroid
		PARENT: Small body

			NAME: Micrometeroid
			DESCRIPTION: A very little meteroid
			PRODUCT: Micrometeroid
			PARENT: Meteroid

	NAME: Star
	DESCRIPTION: A star is a celestial body that has termonuclear reaction in its core, for that shine of its own light. Stars have a mass between 0.08 and 200 Sun Masses. Lighter objects are called brown dwarfs, and they don't produce energy via nuclear fusion
	MASS MAX: 3.97784e32
	MASS MIN: 9241818000
	PARENT: Celestial object

			NAME: Black hole
			DESCRIPTION: A so massive and dense body that even the light can't escape from it
			MASS MIN: 21.77
			BLUE MAX: 0
			RED MAX: 0
			GREEN MAX: 0
			PARENT: Star

			NAME: White dwarf
			PARENT: Star
			
		NAME: Neutron star
		PARENT: Compact star

			NAME: Pulsar
			PARENT: Neutron star
	
			NAME: Magnetar
			DESCRIPTION: A magnetar is a Neutron star whit a very strong magnetic field
			PARENT: Neutron star
	
	NAME: Planet
	DESCRIPTION: A planet is a celestial body that is rounded by its own gravity because is massive enought, has cleared its neightbouring region of planetesimal and doesn't have thermonuclear fusion into it for is mass
	PARENT: Celestial object

		NAME: Chthonian planet
		DESCRIPTION: A chtonian planet is a planet generated from the hydrodinamic escape of a Gas Giant atmosphere. The remaining metal and rocky core form this planet
		PARENT: Planet

		NAME: Giant planet
		MASS MAX: 2.467647e28
		PARENT: Planet

			NAME: Gas giant
			PARENT: Giant planet

			NAME: Ice giant
			PARENT: Giant planet
			
				NAME: Mini-Neptune
				DESCRIPTION: An ice giant similar to Neptune, but littler
				MASS MAX: 1e26
				PARENT: Planet

		NAME: Iron planet
		DESCRIPTION: An iron planet is a planet whit the core composed mainly of iron and whit a very little mantle or whitout any mantle at all
		PARENT: Planet
		
		NAME: Minor planet
		DESCRIPTION: A minor planet is a massive body that doesn't have all the requisites to be a planet
		PARENT: Celestial object

			NAME: Asteroid
			DESCRIPTION: An asteroid is a minor planet that has a composition very similar to a terrestrial planet. Asteroid composed meanly by ice are called comets, some asteroids are comets that have lose their ice
			PRODUCT: Meteroid
			PARENT: Minor planet
		
			NAME: Dwarf planet
			DESCRIPTION: A dwarf planet is a planetary mass object enought massive to have an hydrostatic equilibrium, but not enought to clear the materials in the neightbouroud space
			PARENT: Minor planet
	
		NAME: Terrestrial planet
		DESCRIPTION: A terrestrial planet is a planet composed mainly by rock and metal
		PARENT: Planet

			NAME: Earth analog
			DESCRIPTION: An Earth analog is a terrestrial planet much similar to the Earth
			PARENT: Terrestrial planet

			NAME: Super Earth
			DESCRIPTION: A super Earth is a terrestrial planet massive two to five Earth masses, more massive terrestrial planet are called Mega Earth
			MASS MAX: 29.863e24
			MASS MIN: 11e24
			PARENT: Terrestrial planet

			NAME: Mega Earth
			DESCRIPTION: A Mega Earth is a terrestrial planet ten or more times more massive than Earth, even more massive than super-Earths that are five to ten times more massive than Earth 
			MASS MAX: 6e25
			MASS MIN: 298e23
			PARENT: Terrestrial planet

########################################################################
#	ORGANIC
#
NAME: Organic Matter
HUNTED: N
DESCRIPTION: Matter composed of carbon compound, it's life or a life product
PRODUCT: Organic Matter
MERGE: N
PARENT: Object

	NAME: Space Monster
	DESCRIPTION: As in the old times big and unknown creatures have terrorized for years the men of the sea, now space monsters' legends terrorize the men in our modern times. Are they real or are only a legend?
	HUNTED: N
	HUNTER: Y
	PARENT: Organic Matter

		NAME: Deep Space Kraken
		DESCRIPTION: Terrifying huge creature that destroy anything encouters
		PARENT: Space Monster
	
		NAME: Leviatan
		DESCRIPTION: Huge dragon of the space, the information about him are very few
		PARENT: Space Monster

	NAME: Tux
	DESCRIPTION: Our hero!
	PARENT: Object

EOF
(END OF FILE)
