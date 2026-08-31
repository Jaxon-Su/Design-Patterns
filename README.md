# C++ 設計模式中文學習筆記

這是一份原創的 C++ 設計模式學習專案，用不同情境示範 GoF 常見設計模式的精神。  
本專案不搬運付費範例程式碼，只保留設計模式名稱與學習脈絡，適合放到 GitHub 作為個人備份與複習材料。

## 如何執行

需要 C++17 編譯器。

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\design_patterns_demo.exe
```

若使用 MinGW 或單一組態產生器，執行檔可能在：

```powershell
.\build\design_patterns_demo.exe
```

## 內容

| 分類 | 模式 |
|---|---|
| 建立型 | Abstract Factory、Builder、Factory Method、Prototype、Singleton |
| 結構型 | Adapter、Bridge、Composite、Decorator、Facade、Flyweight、Proxy |
| 行為型 | Chain of Responsibility、Command、Iterator、Mediator、Memento、Observer、State、Strategy、Template Method、Visitor |

## 檔案

- `docs/patterns.md`：中文觀念、適用時機、原創生活化例子
- `examples/design_patterns_demo.cpp`：可編譯的 C++17 範例

## 學習建議

1. 先讀 `docs/patterns.md` 的「一句話」與「適合用在」。
2. 再看 `examples/design_patterns_demo.cpp` 對應 namespace。
3. 嘗試把範例換成自己的專案情境，例如儀器控制、報表分析、UI 流程或資料轉換。

