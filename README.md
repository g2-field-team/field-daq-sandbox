# field-daq-sandbox

A clone of the main field-daq repo where we can all write the homework front-ends we had talked about in the workshop.  

## Setup
1. Install screen if not installed, `sudo yum install screen`
2. Clone the repo, `cd ~/Applications && git clone https://github.com/g2-field-team/field-daq-sandbox.git`
3. Add the experiment to the exptab, `echo "daq-sandbox /home/$USER/Applications/field-daq-sandbox/resources $USER" | sudo tee --append /etc/exptab`
4. Add data structure to field-core if using c struct
5. Copy frontend common/template/frontend.cxx to online/frontends/src/
6. Modify all text/lines marked with '@' symbol
7. Either add an init script for ODB parameters (common/odb.d/*.cmd) used by the frontend or add them in frontend init code
5. Run the ODB initialization script in common, `./init-odb.sh`
6. Edit common/.expt-env to launch front-end with daq control scripts
7. Start the daq, `./online/bin/start_daq.sh`
8. Check the browser at http://localhost:8082
