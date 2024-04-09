#ifndef TRACKVIEW_H
#define TRACKVIEW_H

/********************************************//**
 *  Class name: TrackView
 *  Function: Track level GUI class
 ***********************************************/

class TrackView
{
public:

    void init();
    void tick();

    void paint();

private:

    // pitch shifter view
    // waveshaper view
    // filter view
    // reverb view
    // delay view

    bool isOpen;
    int trackID;
};

#endif