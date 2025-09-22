# Minishell

## Recursos
- GNU Bash manual: [HTML (one page)](https://www.gnu.org/software/bash/manual/bash.html) | [HTML](https://www.gnu.org/software/bash/manual/html_node/index.html) | [PDF](https://www.gnu.org/software/bash/manual/bash.pdf)
- The Open Group: [Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- Gustavo Junipero y Justin Ennen: [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/)
- Otras minishells: [A. Pérez y M. Bueno](https://github.com/madebypixel02/minishell) | [J. Castro y M. Parra](https://github.com/lvzrr/minishell) | [D. Jiménez e I. Sainz](https://github.com/BishopVK/minishell)
- Guías 42: [42 Cursus Guide](https://42-cursus.gitbook.io/guide/3-rank-03/minishell)
- 42 Evaluation Sheets Hub: [Minishell](https://42sheets.eina.cc/Cursus/Minishell/)

## Requisitos

Tu shell deberá:
- Mostrar una entrada mientras espera un comando nuevo.
- Tener un historial funcional.
- Buscar y ejecutar el ejecutable correcto (basado en la variable `PATH` o mediante el uso de rutas relativas
o absolutas).
- Evita utilizar más de una variable global para indicar la recepción de una señal. Piensa en lo que implica:
Esta aproximación evita que tu gestor de señales acceda a tus estructuras de datos principales.

¡Cuidado! Esta variable global no puede proporcionar ninguna otra información o datos que el número de una señal recibida. Por lo tanto está prohibido utilizar estructuras de tipo "norm" en global.

- No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como `\`
(barra invertida) o `;` (punto y coma).
- Gestionar que la `'` evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
- Gestionar que la `"` evite que el shell interprete los metacaracteres en la secuencia entrecomillada
exceptuando `$` (signo de dólar).
- Implementar redirecciones:
  - `<` debe redirigir input.
  - `>` debe redirigir output.
  - `>>` debe redirigir el output en modo append.
  - `<<` debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que
contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial.
- Implementar pipes (carácter `|` ). El output de cada comando en la pipeline se conecta a través de un pipe
al input del siguiente comando.
- Gestionar las variables de entorno ( `$` seguidos de caracteres) que deberán expandirse a sus valores.
- Gestionar `$?` , que deberá expandirse al estado de salida del comando más reciente ejecutado en la
pipeline.
- Gestionar `Ctrl`+`C` , `Ctrl`+`D` y `Ctrl`+`\` , que deberán funcionar como en Bash.
- Cuando sea interactivo:
  - `Ctrl`+`C` imprime una nueva entrada en una línea nueva.
  - `Ctrl`+`D` termina el shell.
  - `Ctrl`+`\` no hace nada.
- Deberá implementar los built-ins:
  - `echo` con la opción `-n`.
  - `cd` solo con una ruta relativa o absoluta.
  - `pwd` sin opciones.
  - `export` sin opciones.
  - `unset` sin opciones.
  - `env` sin opciones o argumentos.
  - `exit` sin opciones.

Limítate a hacer lo que pide el enunciado. Cualquier cosa no solicitada no se requiere.

Para cada punto, y en caso de dudas, puedes utilizar [Bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) como una referencia.

### Bonus

Tu programa deberá implementar los siguientes puntos:

- `&&`, `||` con paréntesis para prioridades.
- Los wildcards `*` deben funcionar para el directorio actual.

## Funciones autorizadas

Se permite usar `libft`.

La función `readline` puede producir algunos leaks que no necesitas arreglar. Eso no signiﬁca que tu código, sí, el código que has escrito, pueda producir leaks.

```c
char *readline(char *promt);
? rl_clear_history(?);
? rl_on_new_line(?);
? rl_replace_line(?);
? rl_redisplay(?);
void add_history(char *string);

int printf(char *format, ...);
void *malloc(size_t size);
void *free(void *p);

ssize_t write(int fd, void *buf, size_t count);
int access(char *pathname, int mode);
int open(char *pathname, int flags);
ssize_t read(int fd, void *buf, size_t count);
int close(int fd);

pid_t fork(void);
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
pid_t wait3(int wstatus, int options, struct rusage rusage);
pid_t wait4(pid_t pid, int wstatus, int options, struct rusage rusage);

? signal(?);
int sigaction(int signum, struct sigaction act, struct sigaction oldact);
int kill(pid_t pid, int sig);
void exit(int status);

char *getcwd(char buf[size], size_t size);
int chdir(char *path);

int stat(char *path, struct stat statbuf);
int lstat(char *path, struct stat statbuf);
int fstat(int fd, struct stat statbuf);

int unlink(char *path);

int execve(char *path, char *argv[], char *envp[]);
int dup(int oldfd);
int dup2(int oldfd, int newfd);
int pipe(int pipefd[2]);

DIR *opendir(char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

char *strerror(int errnum);
void perror(char *str);

int isatty(int fd);
char **ttyname(int fd);
int ttyslot(void);

int ioctl(int fd, unsigned long request, ...);

char *getenv(const char *name);

int tcsetattr(int fildes, int optional_actions, const struct *termios_p);
int tcgetattr(int fildes, struct termios *termios_p);

int tgetent(char *bp, const char *name);
int tgetflag(char *id);
int tgetnum(char *id);
char *tgetstr(char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
```
