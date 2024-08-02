bool Mouse::zabelezi(bool r) {
    lastX = x;
    lastY = y;
    lastButtons = buttons;
    left = buttons & SDL_BUTTON_LMASK;
    right = buttons & SDL_BUTTON_RMASK;
    return r;
}

bool Mouse::update(bool &but) {
    buttons = SDL_GetMouseState(&x, &y);
    int out = 0;
    but = (buttons != lastButtons);
    if (but || (x != lastX || y != lastY)) return zabelezi(true);
    return zabelezi(false);
}