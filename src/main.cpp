#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <cmath>

// Estructuras de datos básicas para el motor
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

// --- SISTEMA DE NODOS PROFESIONAL ---
class Node {
public:
    std::string name;
    std::vector<std::shared_ptr<Node>> children;
    Vector3 position = {0.0f, 0.0f, 0.0f};
    bool active = true;

    Node(std::string n) : name(n) {}
    virtual ~Node() = default;

    void addChild(std::shared_ptr<Node> child) {
        children.push_back(child);
    }

    // Actualización lógica recursiva
    virtual void update(float deltaTime) {
        if (!active) return;
        for (auto& child : children) {
            child->update(deltaTime);
        }
    }

    // Renderizado recursivo
    virtual void render() {
        if (!active) return;
        for (auto& child : children) {
            child->render();
        }
    }
};

// --- NODOS 3D (Mundo) ---
class Node3D : public Node {
public:
    Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Node3D(std::string n, Vector3 pos) : Node(n) { position = pos; }

    void update(float deltaTime) override {
        rotation.y += 1.5f * deltaTime; // Rotación constante
        Node::update(deltaTime);
    }

    void render() override {
        // Aquí irían los comandos de dibujo 3D (OpenGL)
        std::cout << "[Render 3D] Dibujando nodo: " << name << " en posicion: " << position.x << std::endl;
        Node::render();
    }
};

// --- NODOS 2D (Interfaz / HUD) ---
class Node2D : public Node {
public:
    float scale = 1.0f;
    Node2D(std::string n, float x, float y) : Node(n) { position = {x, y, 0.0f}; }

    void render() override {
        // Aquí irían los comandos de dibujo 2D (Sprites / Texto)
        std::cout << "[Render 2D] Dibujando interfaz: " << name << " en pantalla" << std::endl;
        Node::render();
    }
};

// --- EL CORAZÓN DEL MOTOR (OrangyCore) ---
class OrangyEngine {
public:
    OrangyEngine() {
        worldRoot = std::make_shared<Node>("WorldRoot");
        uiRoot = std::make_shared<Node>("UIRoot");
    }

    void init() {
        std::cout << "========================================" << std::endl;
        std::cout << "   ORANGY ENGINE PRO - INICIALIZANDO    " << std::endl;
        std::cout << "========================================" << std::endl;

        // Crear una escena de prueba masiva
        for(int i = 0; i < 10; ++i) {
            auto building = std::make_shared<Node3D>("Building_" + std::to_string(i), Vector3{(float)i * 5.0f, 0.0f, -10.0f});
            worldRoot->addChild(building);
        }

        // Crear interfaz
        auto healthBar = std::make_shared<Node2D>("HealthBar", 20.0f, 20.0f);
        uiRoot->addChild(healthBar);
        
        std::cout << "[OrangyEngine] Motor listo para arrancar." << std::endl;
    }

    void run() {
        auto lastTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;

        // Game Loop (Simulación de 100 frames para el CI/CD)
        while (frameCount < 100) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

            update(deltaTime);
            render();

            frameCount++;
        }
        
        std::cout << "========================================" << std::endl;
        std::cout << "   ORANGY ENGINE - CIERRE CORRECTO      " << std::endl;
        std::cout << "========================================" << std::endl;
    }

private:
    std::shared_ptr<Node> worldRoot;
    std::shared_ptr<Node> uiRoot;

    void update(float dt) {
        worldRoot->update(dt);
        uiRoot->update(dt);
    }

    void render() {
        // 1. Limpiar pantalla (Comandos OpenGL reales irían aquí)
        // 2. Dibujar mundo 3D
        worldRoot->render();
        // 3. Dibujar UI (encima del mundo)
        uiRoot->render();
    }
};

int main() {
    OrangyEngine engine;
    engine.init();
    engine.run();
    return 0;
}
