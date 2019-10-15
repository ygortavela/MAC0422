# **MAC0422 - SISTEMAS OPERACIONAIS**

## Relatório EP2

------

### **Washington Luiz - 10737157**

### **Ygor Tavela Alves - 10687642**

## 1. **Prioridade BATCH_Q**

------

A macro **BATCH_Q** foi adicionada entre o **IDLE** e as filas de usuário. Para isso, aumentamos o número de filas (**NR_SCHED_QUEUES**) para **17** e o **IDLE** foi definido como **16**, **BATCH_Q** corresponde à fila **15**. Essa mudança foi realizada em */kernel/proc.h* .

## 2/3. ***System calls batch* e *unbatch***

------

Para fazer o **item 2** e **3**, ou seja, implementar as chamadas de sistema *batch* e *unbatch*, foi necessário implementar uma *chamada de kernel* (system task *setprior*) auxiliar. Abaixo descrevemos o *workflow* delas.

<u>Chamada de sistema **batch**/**unbatch**:</u>

- Parâmetros: **PID** do processo que deve entrar/sair na fila **BATCH_Q**;
- Rotina:
   1. Em *src/lib/posix/[_batch.c | _unbatch]* (com protótipo em header *unistd.h*) é criado uma nova *message* **m**, contendo o **PID** do processo e o **PID** do processo de quem a invocou;
   2. Envia **m** ao *process manager* (**MM**), indicando qual a rotina (**BATCH**/**UNBATCH**) deve ser chamada: ***_syscall(MM, BATCH/UNBATCH, &m)***. Sendo as macros **BATCH**/**UNBATCH** definidas em *src/include/minix/callnr.h* e, mapeadas na tabela de rotinas em *src/server/pm/table.c*, cujas rotinas correspondentes são **do_batch**/**do_unbatch**;
   3. Chama a rotina **do_batch**/**do_unbatch** (*src/server/pm/misc.c*) que extrai os parâmetros de **m** e, verifica se o processo que a chamou é **pai** do processo (**filho**) que deve entar/sair na fila **BATCH_Q**. Se for o caso, é feito uma *chamada de kernel* **sys_setprior**, parametrizada com o número do processo **filho** na tabela de processos e com a nova fila de prioridade, a qual, o processo deve entrar.
- Obs.: a diferença de batch pra unbatch é que a primeira coloca na fila BATCH_Q e a segunda tira da BATCH_Q , colocando na fila USER_Q.

<u>Chamada de kernel **sys_setprior**:</u>

- Parâmetros: o número do processo e a nova fila prioridade;
- Rotina:
  1. Em *src/lib/syslib/sys_setprior.c* é passado os parâmetros para o ponteiro *message* **m**;
  2. Envia **m** para o *system task* (**SYSTASK**), indicando qual rotina (**SYS_SETPRIOR**) a ser chamada: ***_taskcall(SYSTASK, SYS_SETPRIOR, &m)***. Sendo a macro  **SYS_SETPRIOR** definida em *src/include/minix/com.h* e, mapeada em *src/kernel/system.c*;
  3. Chama a rotina **do_setprior** (*src/kernel/system/do_setprior.c*). Ela extrai os parâmetros da mensagem **m**, o número do processo (**proc_nr**) e sua prioriade (**pri**). Com o número do processo recuperamos um apontador para processo (**rp**) atráves da rotina **proc_addr**. Finalmente, chamados a função **lock_dequeue**, a qual tira o processo da fila, bloqueando ele, e atualizamos a prioriade do processo, no caso, para **prio**. Assim, chamamos a função **lock_enqueue**, a qual coloca o o processo na fila correspondente à **prio**.


## 4. **Mudanças na política de scheduling**
