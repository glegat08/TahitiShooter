#pragma once

#include <SFML/Graphics.hpp>

class GameObject 
{
public:
    // Constructor & Destructor
    GameObject() = default;
    virtual ~GameObject() = default;

    // Pure virtual methods (state checks)
    virtual bool isAlive() = 0;            // Check if the object is alive
    virtual bool isShooting() = 0;         // Check if the object is shooting
    virtual bool isAttacking() = 0;        // Check if the object is attacking
    virtual bool isInvulnerable() = 0;     // Check if the object is invulnerable

    // Pure virtual methods (actions)
    virtual void setTexture() = 0;               // Set the object's texture
    virtual void updateAnim() = 0;               // Update animation
    virtual void movement() = 0;                 // Handle movement logic

    // Health and Shield Management
    virtual int getHp() = 0;               // Return health points
    virtual int getShield() = 0;           // Return shield points
    virtual void takeDamage(int damage) = 0;     // Handle damage received
    virtual void setInvulnerable(float duration) = 0; // Set invulnerability duration

    // Weapon Management (for subclasses that need it)
    virtual void getWeapon() = 0;          // Return the current weapon
    virtual void switchWeapon() = 0;             // Switch to a different weapon
};
