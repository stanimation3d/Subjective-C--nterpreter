# Subjective-C Manual (v0.0.1)

Subjective-C is a **Subject-Oriented Programming (SOP)** language that focuses on how objects are perceived in different contexts.

## 1. Core Principles
- **SOP vs OOP:** Instead of "What is this object?", we ask "How does this object appear in this subject?".
- **SBMM:** Memory is managed based on subjects. When a `subject` block ends, all associated variables are automatically deallocated.

## 2. Special Operators & Shortcuts
The language uses unique mathematical symbols. In our dedicated IDE terminal, use the following shortcuts:

| Operation | Symbol | Shortcut |
| :--- | :--- | :--- |
| Addition | `+` | Shift + 4 |
| Subtraction | `-` | Standard `-` |
| Multiplication | `x` | X Key |
| Division | `÷` | Shift + 7 |
| Equality | `=` | Shift + 0 |
| Power | `¹²³...` | Ctrl + Alt Gr + [Number] |

## 3. Syntax Example
```c
İmport Standart;

subject Accounting {
    degisken salary = 5000;
    degisken bonus = salary ÷ 10;
    degisken total = salary + bonus;
} 
// SBMM: 'salary', 'bonus', and 'total' are deleted here.
```
---

## 📝 Future Tasks (To-Do List)

Projenin geleceği için İngilizce olarak hazırladığım yapılacaklar listesi:

* **[LOW]** Implement a `print()` function to display variable values in the terminal.
* **[MEDIUM]** Enhance the **SBMM** logic to support "Subject Inheritance" (A subject viewing another subject's data).
* **[MEDIUM]** Develop a GUI-based IDE using **Qt** or **ImGui** to handle the custom keyboard shortcuts automatically.
* **[HIGH]** Integrate a **Preprocessor** to handle complex superscript expressions like variables raised to variables (e.g., `xⁿ`).
* **[HIGH]** Add support for `.sc` file importing using the `İmport` keyword.

---

## 🛠️ Derleme ve Çalıştırma (Compilation)

Tüm dosyaları (`.hpp` ve `.cpp`) aynı klasöre koyduktan sonra terminalinizde şu komutu çalıştırarak derleme yapabilirsiniz:

### Örneğin g++ için Derleme Komutu:
```bash
g++ -o subc Main.cpp Lexer.cpp Parser.cpp Evaluator.cpp SubjectManager.cpp Token.cpp -std=c++17
```
Execution:
Interactive Terminal: ```bash ./subc```
File Execution:
```
./subc program.sc

```
The initial instruction varies from compiler to compiler.
