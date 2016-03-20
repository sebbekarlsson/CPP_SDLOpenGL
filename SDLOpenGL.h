#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


class SDLOpenGL {
    public:

        int SCALE;
        int WIDTH;
        int HEIGHT;
        bool quit;

        SDL_Window* display = NULL;
        SDL_GLContext context;


        /**
         * Constructor
        */
        SDLOpenGL () {
            this->SCALE = 2;
            this->WIDTH = 640;
            this->HEIGHT = WIDTH / 16 * 9;
            this->quit = false;
        }

        
        /**
         * This function is used to initialize the openGL.
         * @return <bool>
        */
        bool initGL () {
            bool success = true;
            GLenum error = GL_NO_ERROR;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity(); 

            error = glGetError();
            if (error != GL_NO_ERROR) {
                success = false;
            }

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glClearColor(
                    (float)(255/255),
                    (float)(255/255),
                    (float)(255/255),
                    1.0f
                    );


            return success;
        }
        

        /**
         * This function is used to initialize the display/window with
         * the OpenGL context.
         * @return <bool>
        */
        bool init () {
            bool success = true;

            if (!SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("Could not initialize video", SDL_GetError());
                success = false;
            } else {
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

                display = SDL_CreateWindow (
                        "Game Title",
                        0,
                        0,
                        WIDTH * SCALE,
                        HEIGHT * SCALE,
                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
                        );

                if (display == NULL) {
                    printf("Could not create display", SDL_GetError());
                } else {
                    context = SDL_GL_CreateContext(display);

                    if (context == NULL) {
                        printf("Could not create context", SDL_GetError());
                        success = false;
                    } else {
                        if (!initGL()) {
                            printf("Could not initialize OpenGL", SDL_GetError());
                            success = false;
                        }
                    }
                }
            }

            return success;
        }

        
        /**
         * Tick/Update function.
        */
        void update () {
            printf("Update");
        }

        
        /**
         * This function is used to draw a rotating green plane.
        */
        void render () {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glRotatef(0.4f,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
            glRotatef(0.2f,1.0f,1.0f,1.0f);
            glColor3f(0.0f,1.0f,0.0f); 

            glBegin( GL_QUADS );
            glVertex2f( -0.5f, -0.5f );
            glVertex2f( 0.5f, -0.5f );
            glVertex2f( 0.5f, 0.5f );
            glVertex2f( -0.5f, 0.5f );
            glEnd();
        }

        
        /**
         * This function is used to terminating and killing the program.
        */
        void close () {
            SDL_DestroyWindow(display);
            display = NULL;
            SDL_Quit(); 
        }
};
