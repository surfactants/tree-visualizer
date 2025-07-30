# Tree Visualizer
## About
Visualizes n-ary trees using SFML.

## Construction
All behavior is contained within the Tree_Visualizer class. A default constructor is included, but the only way to actually add nodes is through the complete constructor.

First, construct Node_Data objects, which have the following members:
```
	unsigned short int id; // UID
	std::string tval; // the string's data
	std::vector<unsigned short int> children; // UIDs of this node's children
```
These are stored in an std::map, keyed to the node UIDs. This map is passed to the constructor, along with sf::Font and sf::View objects:

```
	Tree_Visualizer(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::View view);
```

## Usage
Left clicking selects nodes (or deselects if no node is moused on click). Middle- and right-clicks control dragging.

There are two functions required for normal operations, to be embedded in the main update/event loops. Both have void return types:
- **update(const sf::Vector2f& translated_mpos)**: the mouse position must be translated according to the view (using MapPixelToCoords or something similar)
- **checkMouse(sf::Event& event)**: Responds to mouse clicks

## Colors
There are multiple functions to handle colors in the visualizer. They all take a single const sf::Color&, and a void return.

### Tree_Visualizer colors:
- **setFrameColor**
- **setTitleColor**

### Node colors:
- **setNodeFillColor**: base circle
- **setNodeTextColor**: base text
- **setNodeHiFillColor**: highlighted circle
- **setNodeHiTextColor**: highlighted text
- **setNodeSelFillColor**: selected circle
- **setNodeSelTextColor**: selected highlight
- **setLineColor**: child lines
These functions operate recursively.

### Node_Info_Display colors:
- **setDisplayFrameColor**: frame
- **setDisplayTextColor**: text/title