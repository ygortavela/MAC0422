# **MAC0422 - SISTEMAS OPERACIONAIS**

## Relatório EP4

------

### **Washington Luiz - 10737157**

### **Ygor Tavela Alves - 10687642**



## 1. **I_TEMPORARY**

------

A macro *I_TEMPORARY* foi adicionada em *usr/src/include/minix/const.h* sendo definida como o número octal **0o030000**.

## 2. ***System call open_tmp***

- Parâmetros:  *strings* **nome** e **modo** de abertura do *file*;
- Rotina:
   1. Em *usr/src/lib/posix/_open_tmp.c* (com protótipo no header *usr/src/include/fcntl.h*) o **modo** de abertura é convertido para um número inteiro de acordo com o tipo da *string* de modo de abertura "r", "w", "a", "r+", "w+" e "a+". Após esse passo, é criado uma nova *message* **m**, contendo o **modo** de abertura e o **nome** do *file* a ser aberto como temporário. 
   2. É dado *dispatch* da message **m** ao *file server* (**FS**) para a chamada **OPENTMP**: ***_syscall(FS, OPENTMP, &m)***. Sendo a macro **OPENTMP** definida em *usr/src/include/minix/callnr.h* e, a chamada em si, mapeada na tabela de rotinas em *usr/src/server/fs/table.c*, cuja rotina correspondente é **do_open_tmp**;
   3. Chama a rotina **do_open_tmp** (*usr/src/server/fs/open.c*) que extrai os parâmetros de **m**, altera o estado de uma variável de escopo global **temp** para **1** e, então, chama a função ***common_open*** (no mesmo arquivo), que foi alterada na linha **100** para setar o *omode* adequado de acordo com o estado da variável **temp**, assim é possível criar um novo inode com modo temporário. Ao final, a variável **temp** é resetado para **0**.
- Observações: Para impedir que arquivos temporários possuam links simbólicos adicionamos uma simples verificação na função **do_slink()** em */usr/src/servers/fs/open.c*, que verifica o **i_mode** do *inode* e caso o seu tipo seja **I_TEMPORARY** ele simplesmente ignora o resto do código da função e retorna com um código de erro.
