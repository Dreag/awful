#include"mpi.h"
#include<iostream>

using namespace std;

// MPI_Type_struct(2 ,blockcounts ,offsets ,oldtypes ,&particletype);

int main(int argc ,char *argv[])
{
    int rank ,numproc ,source = 0  ,tag = 1;

    typedef struct 
    {
        float x ,y ,z;
        float velocity;
        int n ,type;
    }Particle;

    Particle p[25] ,particles[25];
    MPI_Datatype particletype ,oldtypes[2];
    int blockcounts[2];
    MPI_Aint offsets[2] ,extent;        //typedef long MPI_Aint  用来表示地址

    MPI_Status status;

    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);

    offsets[0] = 0;
    oldtypes[0] = MPI_FLOAT;
    blockcounts[0] = 4;

    MPI_Type_extent(MPI_FLOAT ,&extent);    //return the size of the type MPI_FLOAT ，返回该数据类型的一个实例在消息中所占的字节数  
    cout<<"The extent is : "<<extent<<endl; 
    offsets[1] = 4 * extent;
    oldtypes[1] = MPI_INT;
    blockcounts[1] = 2;

    MPI_Type_struct(2 ,blockcounts ,offsets ,oldtypes ,&particletype);
    // bolckcounts : {4 ,2}
    // offsets     : {0 ,16}
    // oldtypes : {MPI_FOLAT ,MPI_INT}
    // typedef struct 
    // {
    //     float x ,y ,z;
    //     float velocity;
    //     int n ,type;
    // }Particle;
    MPI_Type_commit(&particletype);
    
    if(rank == 0)
    {
        for(int i = 0 ;i<25 ;i++)
        {
            particles[i].x = i * 1.0;
            particles[i].y = i * 2.0;
            particles[i].z = i * 3.0;
            particles[i].velocity = 0.25;
            particles[i].n = i;
            particles[i].type = i%2;
        }

        for(int i = 1 ;i<numproc ;i++)
        {
            MPI_Send(particles ,25 ,particletype ,i ,tag ,MPI_COMM_WORLD);
        }
        
    }
    else
    {
        MPI_Recv(p ,25 ,particletype ,0 ,tag ,MPI_COMM_WORLD ,&status);
        cout<<"message 0 :"<<endl;
        cout<<"rank = "<<rank<<' '<<p[0].x<<' '<<p[0].y<<' '<<p[0].z<<' '<<p[0].velocity<<' '<<p[0].n<<' '<<p[0].type<<endl;
        cout<<"message 4 :"<<endl;
        cout<<"rank = "<<rank<<' '<<p[3].x<<' '<<p[3].y<<' '<<p[3].z<<' '<<p[3].velocity<<' '<<p[3].n<<' '<<p[3].type<<endl;
    }

    MPI_Type_free(&particletype);
    MPI_Finalize();
}
