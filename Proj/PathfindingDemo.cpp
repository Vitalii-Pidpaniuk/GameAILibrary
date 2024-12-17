#include "PathfindingDemo.h"

void PathfindingDemo::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Pathfinding", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void PathfindingDemo::initGraph()
{
    // Зберігаємо вершини шляху у множину для швидкого доступу
    vector<string> pathNodes;
    for (const auto& node : path)
    {
        pathNodes.push_back(node.name);
    }

    // Малюємо вершини
    for (auto connection : graph.connections)
    {
        const NodeXY& node = connection.first;

        // Порожній кружечок для вершини
        sf::CircleShape circle(20.f);

        // Якщо вершина в шляху - виділяємо її
        //if (pathNodes.find(node.name))
        if(find(pathNodes.begin(), pathNodes.end(), node.name) != pathNodes.end())
        {
            //circle.setFillColor(sf::Color::Green); // Зелений для вершин на шляху
            circle.setOutlineColor(sf::Color::Red);
        }
        else
        {
            circle.setFillColor(sf::Color::Transparent); // Прозорий для інших вершин
        }
        circle.setOutlineColor(sf::Color::Black);    // Чорний контур
        circle.setOutlineThickness(2.f);            // Товщина контуру
        circle.setPosition(node.position.first - circle.getRadius(), node.position.second - circle.getRadius());
        this->window->draw(circle);

        // Назва вершини всередині кружечка
        sf::Text text;
        text.setFont(font);
        text.setString(node.name);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);        // Текст чорного кольору
        // Вирівнюємо текст, щоб був по центру кружечка
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            node.position.first + textBounds.width / 2,
            node.position.second + textBounds.height / 2 - 5
        );
        this->window->draw(text);
    }

    // Малюємо зв’язки
    for (auto connection : graph.connections)
    {
        const NodeXY& from = connection.first;
        for (Connection& connection : connection.second)
        {
            const NodeXY& to = connection.to;

            // Перевіряємо, чи обидві вершини зв'язку входять до шляху
            bool isPathConnection = (find(pathNodes.begin(), pathNodes.end(), from.name) != pathNodes.end()) && (find(pathNodes.begin(), pathNodes.end(), to.name) != pathNodes.end());

            // Лінія для зв’язку
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(from.position.first, from.position.second), isPathConnection ? sf::Color::Red : sf::Color::Black),
                sf::Vertex(sf::Vector2f(to.position.first, to.position.second), isPathConnection ? sf::Color::Red : sf::Color::Black)
            };

            // Якщо зв'язок входить до шляху, робимо лінію товстішою
            if (isPathConnection)
            {
                for (int offset = -2; offset <= 2; ++offset) // Відхилення для товщини
                {
                    sf::Vertex thickLine[] =
                    {
                        sf::Vertex(sf::Vector2f(from.position.first + offset, from.position.second + offset), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(to.position.first + offset, to.position.second + offset), sf::Color::Red)
                    };
                    this->window->draw(thickLine, 2, sf::Lines);
                }
            }
            else
            {
                this->window->draw(line, 2, sf::Lines);
            }

            // Вага зв'язку
            sf::Text weightText;
            weightText.setFont(font);
            weightText.setString(std::to_string(static_cast<int>(connection.cost)));
            weightText.setCharacterSize(30); // Встановлюємо розмір шрифту для ваги
            weightText.setFillColor(sf::Color::Black);
            float midX = (from.position.first + to.position.first) / 2;
            float midY = (from.position.second + to.position.second) / 2;
            weightText.setPosition(midX, midY);
            this->window->draw(weightText);
        }
    }
}


void PathfindingDemo::initTextures()
{
}

void PathfindingDemo::initPath()
{
    Graph _graph;

    NodeXY n1(300, 700, "n1");
    NodeXY n2(700, 700, "n2");
    NodeXY n3(500, 500, "n3");
    NodeXY n4(800, 400, "n4");
    NodeXY n5(500, 200, "n5");
    NodeXY n6(200, 400, "n6");

    _graph.AddConnection(n1, n2, 7);
    _graph.AddConnection(n1, n3, 9);
    _graph.AddConnection(n1, n6, 14);
    _graph.AddConnection(n2, n1, 7);
    _graph.AddConnection(n2, n3, 10);
    _graph.AddConnection(n2, n4, 15);
    _graph.AddConnection(n3, n1, 9);
    _graph.AddConnection(n3, n2, 10);
    _graph.AddConnection(n3, n4, 11);
    _graph.AddConnection(n3, n6, 2);
    _graph.AddConnection(n4, n2, 15);
    _graph.AddConnection(n4, n3, 11);
    _graph.AddConnection(n4, n5, 6);
    _graph.AddConnection(n5, n4, 6);
    _graph.AddConnection(n5, n6, 9);
    _graph.AddConnection(n6, n5, 9);

    graph = _graph;

    //DijkstraPathfinding pathfinding;
    AStarPathfinding pathfinding;
    //NodeXY n1(300, 700, "n1"), n6(200, 400, "n6");
    //path = *pathfinding.FindPath(graph, n1, n6);

    list<NodeXY>* tempPath = pathfinding.FindPath(_graph, n1, n4);
    if (tempPath == nullptr)
    {
        std::cerr << "ERROR: Pathfinding returned nullptr!" << std::endl;
        return;
    }
    path = *tempPath;
}

void PathfindingDemo::initGUI()
{
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
    {
        cout << "ERROR::GAME::Failed to load font" << endl;
    }
}

void PathfindingDemo::initWorld()
{
}

void PathfindingDemo::initSystems()
{
}


PathfindingDemo::PathfindingDemo()
{

	this->initWindow();
	this->initTextures();
    this->initPath();
	this->initGUI();
	this->initWorld();
	this->initSystems();
}


PathfindingDemo::~PathfindingDemo()
{
	delete this->window;

	for (auto& i : this->textures)
	{
		delete i.second;
	}

}


void PathfindingDemo::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		
		this->render();
	}
}

void PathfindingDemo::SetGraph(Graph Graph)
{
    graph = Graph;
}

void PathfindingDemo::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void PathfindingDemo::updateInput()
{
}

void PathfindingDemo::updateGUI()
{
}

void PathfindingDemo::updateWorld()
{
}

void PathfindingDemo::updateCollision()
{
}

void PathfindingDemo::updateBullets()
{
}

void PathfindingDemo::updateEnemies()
{
}

void PathfindingDemo::updateCombat()
{
}

void PathfindingDemo::update()
{
	this->updateInput();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void PathfindingDemo::renderGUI()
{
	this->window->draw(this->pointText);
}

void PathfindingDemo::renderWorld()
{
	this->window->draw(this->worldBackground);
}


void PathfindingDemo::render()
{
	this->window->clear(sf::Color::White);

	this->renderWorld();


	this->renderGUI();

	this->initGraph();

	this->window->display();
}
