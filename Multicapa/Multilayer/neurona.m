sigmoidea=inline('2.0./(exp(-v)+1.0)-1.0');
dsigmoidea=inline('exp(-v).*1.0./(exp(-v)+1.0).^2.*2.0');
dato=[-1 1 -1];
sal_esp=1;
N1=[0.5 0.5 0.5]; %neurona 1
N2=[0.5 0.5 0.5]; %neurona 2
N3=[0.5 0.5 0.5]; %neurona 3

SN1=sigmoidea(dot(N1,dato));
SN2=sigmoidea(dot(N2,dato));
ent=[-1 SN1 SN2];

vi3=dot(N3,ent);
SN3=sigmoidea(vi3);

%Ahora calculo el delta
deltaN3=(sal_esp-SN3)*dsigmoidea(vi3);