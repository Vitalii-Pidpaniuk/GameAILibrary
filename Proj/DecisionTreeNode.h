#pragma once
#include <iostream>
#include <vector>
#include <memory>

// Base class for decision tree nodes
class DecisionTreeNode {
public:
    virtual ~DecisionTreeNode() = default;

    // Pure virtual function to perform the decision tree algorithm
    virtual DecisionTreeNode* makeDecision() = 0;
};

// Action node class
class Action : public DecisionTreeNode {
public:
    explicit Action(const std::string& actionName) : actionName(actionName) {}

    DecisionTreeNode* makeDecision() override {
        return this;
    }

    void executeAction() const {
        std::cout << "Executing action: " << actionName << std::endl;
    }

private:
    std::string actionName;
};

// Decision node base class
class Decision : public DecisionTreeNode {
public:
    DecisionTreeNode* makeDecision() override {
        DecisionTreeNode* branch = getBranch();
        return branch->makeDecision();
    }

protected:
    virtual DecisionTreeNode* getBranch() = 0;
};

// Float decision node class
class FloatDecision : public Decision {
public:
    FloatDecision(float minValue, float maxValue, DecisionTreeNode* trueNode, DecisionTreeNode* falseNode)
        : minValue(minValue), maxValue(maxValue), trueNode(trueNode), falseNode(falseNode) {}

protected:
    DecisionTreeNode* getBranch() override {
        float value = testValue();
        if (value >= minValue && value <= maxValue) {
            return trueNode;
        }
        else {
            return falseNode;
        }
    }

    virtual float testValue() = 0;

private:
    float minValue;
    float maxValue;
    DecisionTreeNode* trueNode;
    DecisionTreeNode* falseNode;
};

// Multi-decision node class
class MultiDecision : public Decision {
public:
    MultiDecision(const std::vector<DecisionTreeNode*>& daughterNodes) : daughterNodes(daughterNodes) {}

protected:
    DecisionTreeNode* getBranch() override {
        int index = testValue();
        if (index >= 0 && index < daughterNodes.size()) {
            return daughterNodes[index];
        }
        return nullptr; // Handle invalid index case
    }

    virtual int testValue() = 0;

private:
    std::vector<DecisionTreeNode*> daughterNodes;
};

// Example of a concrete FloatDecision implementation
class ExampleFloatDecision : public FloatDecision {
public:
    ExampleFloatDecision(float minValue, float maxValue, DecisionTreeNode* trueNode, DecisionTreeNode* falseNode, float testValue)
        : FloatDecision(minValue, maxValue, trueNode, falseNode), value(testValue) {}

protected:
    float testValue() override {
        return value;
    }

private:
    float value;
};

// Example of a concrete MultiDecision implementation
class ExampleMultiDecision : public MultiDecision {
public:
    ExampleMultiDecision(const std::vector<DecisionTreeNode*>& daughterNodes, int testValue)
        : MultiDecision(daughterNodes), value(testValue) {}

protected:
    int testValue() override {
        return value;
    }

private:
    int value;
};

// Example of a concrete FloatDecision implementation
class HealthDecision : public FloatDecision {
public:
    HealthDecision(float minValue, float maxValue, DecisionTreeNode* trueNode, DecisionTreeNode* falseNode, float currentHealth)
        : FloatDecision(minValue, maxValue, trueNode, falseNode), health(currentHealth) {}

protected:
    float testValue() override {
        return health;
    }

private:
    float health;
};

// Example of a concrete MultiDecision implementation
class EnemyStrengthDecision : public MultiDecision {
public:
    EnemyStrengthDecision(const std::vector<DecisionTreeNode*>& daughterNodes, int enemyStrength)
        : MultiDecision(daughterNodes), strength(enemyStrength) {}

protected:
    int testValue() override {
        return strength;
    }

private:
    int strength;
};
