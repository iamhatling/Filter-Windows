﻿/*
* Copyright © 2017 Cloudveil Technology Inc.  
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

using Filter.Platform.Common.Extensions;
using Citadel.Core.Windows.Util;
using Filter.Platform.Common.Util;
using GalaSoft.MvvmLight.CommandWpf;
using System;
using System.Security;
using Te.Citadel.Extensions;
using Te.Citadel.UI.Models;
using Te.Citadel.UI.Views;
using Te.Citadel.Util;

namespace Te.Citadel.UI.ViewModels
{
    /// <summary>
    /// The LoginViewModel class serves as the ViewModel for the LoginView UserControl.
    /// </summary>
    public class LoginViewModel : BaseCitadelViewModel
    {
        /// <summary>
        /// The model.
        /// </summary>
        private LoginModel m_model = null;

        /// <summary>
        /// Private data member for the public AuthenticateCommand property.
        /// </summary>
        private RelayCommand m_authenticateCommand;

        public LoginViewModel()
        {
            // We have to pass the LoginViewModel into our LoginModel so that changes to the LoginModel can RaisePropertyChanged() on the view model.
            // TODO It would be cleaner to not have two layers of properties like this. Maybe change LoginModel into more of a "function container"
            // and make it do all variable edits directly to LoginViewModel.
            m_model = new LoginModel(this);
        }

        /// <summary>
        /// Command to run an authentication request for the credentials given in the view.
        /// CanExecute looks to the model to see if the current state permits execution of this
        /// action. The actual command itself is sent to the model.
        /// </summary>
        public RelayCommand AuthenticateCommand
        {
            get
            {
                if(m_authenticateCommand == null)
                {
                    m_authenticateCommand = new RelayCommand((Action)(async () =>
                    {
                        try
                        {
                            ViewManager?.PushView(LoginView.ModalZIndex * 2, typeof(ProgressWait));
                            await m_model.Authenticate();
                            ViewManager?.PopView(typeof(ProgressWait));
                        }
                        catch(Exception e)
                        {
                            LoggerUtil.RecursivelyLogException(m_logger, e);
                        }
                    }), m_model.CanAttemptAuthentication);
                }

                return m_authenticateCommand;
            }
        }

        /// <summary>
        /// Binding path for user feedback error messages.
        /// </summary>
        public string ErrorMessage
        {
            get
            {
                return m_model.ErrorMessage;
            }

            set
            {
                m_model.ErrorMessage = value;
                RaisePropertyChanged(nameof(ErrorMessage));
            }
        }

        /// <summary>
        /// Binding path for the username input field.
        /// </summary>
        public string UserName
        {
            get
            {
                return m_model.UserName;
            }

            set
            {
                if(value != null && !value.OIEquals(m_model.UserName))
                {
                    m_authenticateCommand.RaiseCanExecuteChanged();
                    m_model.UserName = value;
                    RaisePropertyChanged(nameof(UserName));
                }
            }
        }

        /// <summary>
        /// Binding path for the password input field.
        /// </summary>
        public SecureString UserPassword
        {
            get
            {
                return m_model.UserPassword;
            }

            set
            {
                if(value != null && !value.OEquals(m_model.UserPassword))
                {
                    m_authenticateCommand.RaiseCanExecuteChanged();

                    m_model.UserPassword = value;
                    RaisePropertyChanged(nameof(UserPassword));
                }
            }
        }
    }
}