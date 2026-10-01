#ifndef SAVEGAME_H
#define SAVEGAME_H

struct GuiApp;
typedef struct GuiApp GuiApp;

int savegame_exists(void);
int savegame_save(const GuiApp *app);
int savegame_load(GuiApp *app);
void savegame_delete(void);

#endif /* SAVEGAME_H */
