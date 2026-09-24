# Code standards

These are the conventions the codebase already follows, written down so that new code and pull requests stay consistent with it.
When in doubt, match the file you are editing: consistency with the surrounding code matters more than any rule below.

## Goal: behave like the original game

D2MOO reimplements the original DLLs, so the first rule is that the code must behave like the game it replaces (1.10f unless stated otherwise).

- Keep the original logic, even where it looks odd. Clean up names and structure, not behaviour.
- Do not change a struct's layout or size, unless the struct is D2MOO's own and says so in a comment (for example `//0x03 (Originally 0x02)`).
- Keep the use of the standard library low where it brings little value, and never let it change the game's behaviour or a struct's layout. Small helpers such as `std::min`/`std::max`, `std::size` and `std::numeric_limits` are already used throughout.

### Bugs from the original game

Bugs that exist in the original game are kept, documented, and labelled `vanilla-bug` on GitHub (see #14).
A fix for such a bug goes behind `NO_BUG_FIX`, which gives back the vanilla behaviour when defined:

```cpp
#ifdef NO_BUG_FIX
    // Original game accepts a value of 2 here, which then indexes past the end of stru_6FD28B68.
    if (bNonWaterSpawn < 0 || bNonWaterSpawn > 2)
#else
    if (bNonWaterSpawn < 0 || bNonWaterSpawn > 1)
#endif
```

Always explain what the original does in the `NO_BUG_FIX` branch.

## Tracing code back to the game

Every function starts with a comment giving its address in the original DLL, and its ordinal if it is exported:

```cpp
//D2Game.0x6FC40380
void __fastcall D2GAME_TARGETS_Last_6FC40380(D2GameStrc* pGame, D2UnitStrc* pUnit)

//D2Common.0x6FD8E7A0 (#10277)
D2UnitStrc* __stdcall INVENTORY_GetFirstItem(D2InventoryStrc* pInventory)
```

When a function exists in more than one supported version, list each one: `//1.10f: D2Common.0x...`, `//1.13c: D2Common.0x...`.

Keep the calling convention (`__fastcall`, `__stdcall`, ...) of the original function. Other DLLs and mods call these functions by address or ordinal.

## Naming

- **Functions** use an upper case pseudo-namespace for the module, then an underscore and a Pascal case name: `INVENTORY_GetItemCount`, `SUNIT_SetUninterruptable`, `ACT1Q2_SeqCallback`.
- **Functions without a confirmed name** keep their address: `sub_6FC49AE0`, or a tentative name with the address as a suffix, such as `D2GAME_PACKETS_SendPacket0xA0_A1_A2_6FC3D610`.
- **Variables, parameters and fields** use Hungarian notation: `p` pointer, `n` integer, `b` boolean, `sz` string, `dw` / `w` for 32 / 16 bit values kept from the original names, `f` for flags. For example `pGame`, `nSkillId`, `bIsLeftSkill`, `szName`.
- **Unknown fields** are named after their offset (`unk0x0C`) and unknown parameters after their position (`a2`), until their use is understood.
- **Structs** end in `Strc` (`D2UnitStrc`); structs mapping a .txt record end in `Txt` (`D2SkillsTxt`); packets are `D2GSPacketSrvXX` / `D2GSPacketCltXX`.
- **Globals** are prefixed with `g` (`gpServer`); a few keep the name the original is known by (`sgptDataTables`). A global whose meaning is not settled keeps its address (`gnGamesGUIDs_6FD447F8`).

Naming things is most of the work on this project, so a rename is a welcome contribution on its own. Say in the pull request what in the function body supports the new name.

## Structs

- Wrap struct definitions with `#pragma pack(push, 1)` and `#pragma pack(pop)` so the layout matches the original byte for byte.
- Put the 1.10f offset of each field in a comment, and the size of the struct next to its name:

```cpp
#pragma pack(push, 1)
struct D2CoordStrc                          //sizeof 0x08
{
    int nX;                                 //0x00
    int nY;                                 //0x04
};
#pragma pack(pop)
```

- Use the fixed width types (`int32_t`, `uint16_t`, ...) for fields, so the size is explicit.

## Code

- Prefer enums and `constexpr` over `#define` for constants and values from the game (`STAT_LEVEL`, `UNIT_PLAYER`, `ITEMTYPE_SCROLL` rather than raw numbers).
- Prefer `std::size(array)` over writing an array's length again as a literal (#174), and `std::numeric_limits<T>` over `INT_MAX` and friends (#171).
- Prefer early `return` / `break` / `continue` over deep nesting, and split complex conditions into several `if` blocks.
- Use `D2_ASSERT` for the original game's assertions, and the pool allocation macros (`D2_ALLOC_STRC_POOL`, `D2_FREE_POOL`, ...) where the original uses its memory pools.
- Braces go on their own line, and every `if`/`for`/`while` body gets braces, even a single statement.
- Indentation differs between modules (tabs in most of D2Common, 4 spaces in most of D2Game). Keep whatever the file already uses.

## Language and tooling

- The DLLs are built with MSVC's default language standard (currently C++14) for 32-bit x86, like the original. Code that needs C++17, such as `inline` variables, does not compile yet. The test projects are built as C++17.
- CI runs clang-tidy with the checks from `source/.clang-tidy`, and most of them are errors. Fix a finding rather than disabling the check, unless it is a false positive.
- Build and test with the CMake presets described in [Advanced build and run](./AdvancedBuildAndRun.md).
