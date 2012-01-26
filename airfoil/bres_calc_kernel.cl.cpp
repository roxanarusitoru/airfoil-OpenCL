//
// auto-generated by op2.m on 30-May-2011 22:03:11
//

// user function

//#include "bres_calc.h"

// host stub function

void op_par_loop_bres_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4,
  op_arg arg5 ){


  int    nargs   = 6;
  op_arg args[6] = {arg0,arg1,arg2,arg3,arg4,arg5};

  int    ninds   = 4;
  int    inds[6] = {0,0,1,2,3,-1};


  cl_int ciErrNum;
  cl_event ceEvent;

  if (OP_diags>2) {
    printf(" kernel routine with indirection: bres_calc \n");
  }

  // get plan

  #ifdef OP_PART_SIZE_3
    int part_size = OP_PART_SIZE_3;
  #else
    int part_size = OP_part_size;
  #endif

  op_plan *Plan = op_plan_get(name,set,part_size,nargs,args,ninds,inds);

  // initialise timers

  double cpu_t1, cpu_t2, wall_t1, wall_t2;
  op_timers(&cpu_t1, &wall_t1);

  // execute plan

  int block_offset = 0;

  //cl_kernel hKernel = compileKernel( bres_calc_src, "op_cuda_bres_calc" );
  cl_kernel hKernel = getKernel( "op_cuda_bres_calc" );

  for (int col=0; col < Plan->ncolors; col++) {

  #ifdef OP_BLOCK_SIZE_3
    const size_t nthread = OP_BLOCK_SIZE_3;
  #else
    const size_t nthread = OP_block_size;
  #endif

    const size_t nblocks = Plan->ncolblk[col];
    const size_t n_tot_thread = nblocks * nthread;

    const size_t nshared = Plan->nshared;




    LOG( LOG_INFO, "calling kernel... " );

    ciErrNum = CL_SUCCESS;
    int i = 0;
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &(arg0.data_d));
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_maps[0]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &(arg2.data_d));
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_maps[1]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &(arg3.data_d));
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_maps[2]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &(arg4.data_d));
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_maps[3]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->loc_maps[0]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->loc_maps[1]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->loc_maps[2]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->loc_maps[3]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->loc_maps[4]);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &arg5.data_d);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_sizes);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->ind_offs);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(int), &block_offset);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->blkmap);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->offset);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->nelems);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->nthrcol);
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &Plan->thrcol);
    ciErrNum |= clSetKernelArg(hKernel, i++, nshared, NULL );
    ciErrNum |= clSetKernelArg(hKernel, i++, sizeof(cl_mem), &g_const_d);
    assert_m( ciErrNum == CL_SUCCESS, "error setting kernel arguments" );

    ciErrNum = clEnqueueNDRangeKernel( cqCommandQueue, hKernel, 1, NULL, &n_tot_thread, &nthread, 0, NULL, &ceEvent );
    assert_m( ciErrNum == CL_SUCCESS, "error executing kernel" );

#ifndef ASYNC
    ciErrNum = clFinish( cqCommandQueue );
    assert_m( ciErrNum == CL_SUCCESS, "error completing device commands" );

#ifdef PROFILE
    cl_ulong tqueue, tsubmit, tstart, tend, telapsed;
    ciErrNum = clGetEventProfilingInfo( ceEvent, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &tqueue, NULL );
    ciErrNum |= clGetEventProfilingInfo( ceEvent, CL_PROFILING_COMMAND_SUBMIT, sizeof(cl_ulong), &tsubmit, NULL );
    ciErrNum |= clGetEventProfilingInfo( ceEvent, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &tstart, NULL );
    ciErrNum |= clGetEventProfilingInfo( ceEvent, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &tend, NULL );
    assert_m( ciErrNum == CL_SUCCESS, "error getting profiling info" );
    OP_kernels[3].queue_time      += (tsubmit - tqueue);
    OP_kernels[3].wait_time       += (tstart - tsubmit);
    OP_kernels[3].execution_time  += (tend - tstart);
#endif
#endif

    LOG( LOG_INFO, "OK\n" );


    block_offset += nblocks;
  }

  // update kernel record

  op_timers(&cpu_t2, &wall_t2);
  op_timing_realloc(3);
  OP_kernels[3].name      = name;
  OP_kernels[3].count    += 1;
  OP_kernels[3].time     += wall_t2 - wall_t1;
  OP_kernels[3].transfer  += Plan->transfer;
  OP_kernels[3].transfer2 += Plan->transfer2;
}


