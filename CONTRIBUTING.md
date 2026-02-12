# Contributing to ESP32 Bluetooth Game Controller

Thank you for your interest in contributing! This document provides guidelines for contributing to this project.

## How to Contribute

### Reporting Bugs

If you find a bug, please create an issue with:
- Clear description of the problem
- Steps to reproduce
- Expected vs actual behavior
- Your hardware setup (ESP32 model, joystick type)
- Arduino IDE and library versions
- Serial Monitor output (if applicable)
- Photos of your wiring (if hardware related)

### Suggesting Features

Feature requests are welcome! Please:
- Check if the feature already exists
- Describe the use case clearly
- Explain how it benefits users
- Consider if it fits the project scope

### Code Contributions

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes**
   - Follow existing code style
   - Comment your code
   - Test thoroughly
4. **Commit with clear messages**
   ```bash
   git commit -m "Add: new feature description"
   ```
5. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```
6. **Create a Pull Request**

## Code Style Guidelines

### Arduino/C++ Code

```cpp
// Use meaningful variable names
int joystickXValue;  // Good
int jx;              // Avoid

// Comment complex logic
// Apply exponential moving average filter for smooth response
filteredValue = (alpha * raw) + ((1.0 - alpha) * filtered);

// Use consistent indentation (2 spaces)
if (condition) {
  doSomething();
}

// Define constants at the top
#define PIN_JOYSTICK_X 34
#define DEADZONE 100
```

### Documentation

- Keep documentation up to date with code changes
- Use clear, simple language
- Include examples where helpful
- Add diagrams for complex concepts

## Testing

Before submitting:
1. Test on actual hardware
2. Verify with multiple games if possible
3. Check that existing functionality still works
4. Test edge cases

## Types of Contributions Needed

### High Priority
- Bug fixes
- Hardware compatibility improvements
- Game-specific configurations
- Performance optimizations

### Medium Priority
- Additional examples
- Better documentation
- Improved troubleshooting guides
- New features

### Always Welcome
- Typo fixes
- Clarifying documentation
- Adding comments to code
- Improving README

## Hardware Contributions

If you test with different hardware:
- Document what worked/didn't work
- Share pin configurations
- Note any required code changes
- Add to compatibility list

## Game Configurations

Tested a game successfully?
1. Add entry to GAME_SETUP.md
2. Include controller mapping
3. Note any special settings
4. Share sensitivity recommendations

## Example Contributions

Created a useful example?
1. Add to EXAMPLES.md
2. Include clear comments
3. Explain the use case
4. Keep it simple and focused

## Pull Request Process

1. **Update documentation** if needed
2. **Add yourself** to contributors list (if you want)
3. **Describe changes** in PR description
4. **Link related issues** if applicable
5. **Be responsive** to feedback

## Code Review

- All PRs require review
- Be open to feedback
- Expect iteration
- Stay professional and friendly

## Community Guidelines

- Be respectful and inclusive
- Help others learn
- Share knowledge generously
- Give credit where due
- Focus on constructive feedback

## Questions?

- Open an issue for questions
- Tag with "question" label
- Check existing issues first
- Be specific about what you need help with

## Recognition

Contributors are recognized in:
- GitHub contributors list
- Commit history
- README acknowledgments (for significant contributions)

## Development Setup

1. **Install Arduino IDE** (1.8.13 or higher)
2. **Add ESP32 support**
3. **Install libraries**:
   - ESP32-BLE-Gamepad (0.5.0+)
4. **Connect ESP32** hardware
5. **Test existing code** before making changes

## Commit Message Format

```
Type: Short description

Longer explanation if needed

Fixes #123 (if applicable)
```

**Types:**
- `Add:` New feature
- `Fix:` Bug fix
- `Update:` Modify existing feature
- `Docs:` Documentation changes
- `Refactor:` Code restructuring
- `Test:` Testing related

## What NOT to Contribute

- Unrelated features
- Breaking changes without discussion
- Malicious code
- Copyrighted content
- Dependencies that bloat the project

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Getting Started

Not sure where to start? Look for:
- Issues labeled "good first issue"
- Documentation improvements
- Testing requests
- Example additions

## Thank You!

Every contribution, no matter how small, is appreciated. Thank you for making this project better!

---

For questions about contributing, open an issue with the "question" label.
